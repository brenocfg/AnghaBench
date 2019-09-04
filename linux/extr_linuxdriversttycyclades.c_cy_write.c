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
struct tty_struct {int /*<<< orphan*/  hw_stopped; int /*<<< orphan*/  stopped; int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct TYPE_6__ {int xmit_bytes; int /*<<< orphan*/  xmit_idle; } ;
struct TYPE_4__ {scalar_t__ xmit_buf; } ;
struct cyclades_port {int xmit_cnt; int xmit_head; TYPE_3__ idle_stats; TYPE_2__* card; TYPE_1__ port; } ;
struct TYPE_5__ {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int min (int,int) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_xmit (struct cyclades_port*) ; 

__attribute__((used)) static int cy_write(struct tty_struct *tty, const unsigned char *buf, int count)
{
	struct cyclades_port *info = tty->driver_data;
	unsigned long flags;
	int c, ret = 0;

#ifdef CY_DEBUG_IO
	printk(KERN_DEBUG "cyc:cy_write ttyC%d\n", info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_write"))
		return 0;

	if (!info->port.xmit_buf)
		return 0;

	spin_lock_irqsave(&info->card->card_lock, flags);
	while (1) {
		c = min(count, (int)(SERIAL_XMIT_SIZE - info->xmit_cnt - 1));
		c = min(c, (int)(SERIAL_XMIT_SIZE - info->xmit_head));

		if (c <= 0)
			break;

		memcpy(info->port.xmit_buf + info->xmit_head, buf, c);
		info->xmit_head = (info->xmit_head + c) &
			(SERIAL_XMIT_SIZE - 1);
		info->xmit_cnt += c;
		buf += c;
		count -= c;
		ret += c;
	}
	spin_unlock_irqrestore(&info->card->card_lock, flags);

	info->idle_stats.xmit_bytes += ret;
	info->idle_stats.xmit_idle = jiffies;

	if (info->xmit_cnt && !tty->stopped && !tty->hw_stopped)
		start_xmit(info);

	return ret;
}