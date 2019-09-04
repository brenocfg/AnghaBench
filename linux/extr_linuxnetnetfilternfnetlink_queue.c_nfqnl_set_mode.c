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
struct nfqnl_instance {unsigned char copy_mode; unsigned int copy_range; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NFQNL_COPY_META 130 
#define  NFQNL_COPY_NONE 129 
#define  NFQNL_COPY_PACKET 128 
 unsigned int NFQNL_MAX_COPY_RANGE ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfqnl_set_mode(struct nfqnl_instance *queue,
	       unsigned char mode, unsigned int range)
{
	int status = 0;

	spin_lock_bh(&queue->lock);
	switch (mode) {
	case NFQNL_COPY_NONE:
	case NFQNL_COPY_META:
		queue->copy_mode = mode;
		queue->copy_range = 0;
		break;

	case NFQNL_COPY_PACKET:
		queue->copy_mode = mode;
		if (range == 0 || range > NFQNL_MAX_COPY_RANGE)
			queue->copy_range = NFQNL_MAX_COPY_RANGE;
		else
			queue->copy_range = range;
		break;

	default:
		status = -EINVAL;

	}
	spin_unlock_bh(&queue->lock);

	return status;
}