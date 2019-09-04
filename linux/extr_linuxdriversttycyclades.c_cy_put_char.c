#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  xmit_idle; int /*<<< orphan*/  xmit_bytes; } ;
struct TYPE_4__ {unsigned char* xmit_buf; } ;
struct cyclades_port {int xmit_cnt; int xmit_head; TYPE_3__* card; TYPE_2__ idle_stats; TYPE_1__ port; } ;
struct TYPE_6__ {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cy_put_char(struct tty_struct *tty, unsigned char ch)
{
	struct cyclades_port *info = tty->driver_data;
	unsigned long flags;

#ifdef CY_DEBUG_IO
	printk(KERN_DEBUG "cyc:cy_put_char ttyC%d\n", info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_put_char"))
		return 0;

	if (!info->port.xmit_buf)
		return 0;

	spin_lock_irqsave(&info->card->card_lock, flags);
	if (info->xmit_cnt >= (int)(SERIAL_XMIT_SIZE - 1)) {
		spin_unlock_irqrestore(&info->card->card_lock, flags);
		return 0;
	}

	info->port.xmit_buf[info->xmit_head++] = ch;
	info->xmit_head &= SERIAL_XMIT_SIZE - 1;
	info->xmit_cnt++;
	info->idle_stats.xmit_bytes++;
	info->idle_stats.xmit_idle = jiffies;
	spin_unlock_irqrestore(&info->card->card_lock, flags);
	return 1;
}