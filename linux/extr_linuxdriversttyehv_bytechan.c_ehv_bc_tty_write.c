#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_struct {struct ehv_bc_data* driver_data; } ;
struct ehv_bc_data {unsigned int head; int /*<<< orphan*/  lock; scalar_t__ buf; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int BUF_SIZE ; 
 unsigned int CIRC_SPACE_TO_END (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ehv_bc_tx_dequeue (struct ehv_bc_data*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ehv_bc_tty_write(struct tty_struct *ttys, const unsigned char *s,
			    int count)
{
	struct ehv_bc_data *bc = ttys->driver_data;
	unsigned long flags;
	unsigned int len;
	unsigned int written = 0;

	while (1) {
		spin_lock_irqsave(&bc->lock, flags);
		len = CIRC_SPACE_TO_END(bc->head, bc->tail, BUF_SIZE);
		if (count < len)
			len = count;
		if (len) {
			memcpy(bc->buf + bc->head, s, len);
			bc->head = (bc->head + len) & (BUF_SIZE - 1);
		}
		spin_unlock_irqrestore(&bc->lock, flags);
		if (!len)
			break;

		s += len;
		count -= len;
		written += len;
	}

	ehv_bc_tx_dequeue(bc);

	return written;
}