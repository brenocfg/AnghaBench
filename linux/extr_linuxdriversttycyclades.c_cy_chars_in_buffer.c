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
struct tty_struct {int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct cyclades_port {int xmit_cnt; } ;

/* Variables and functions */
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cy_chars_in_buffer(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;

	if (serial_paranoia_check(info, tty->name, "cy_chars_in_buffer"))
		return 0;

#ifdef Z_EXT_CHARS_IN_BUFFER
	if (!cy_is_Z(info->card)) {
#endif				/* Z_EXT_CHARS_IN_BUFFER */
#ifdef CY_DEBUG_IO
		printk(KERN_DEBUG "cyc:cy_chars_in_buffer ttyC%d %d\n",
			info->line, info->xmit_cnt);
#endif
		return info->xmit_cnt;
#ifdef Z_EXT_CHARS_IN_BUFFER
	} else {
		struct BUF_CTRL __iomem *buf_ctrl = info->u.cyz.buf_ctrl;
		int char_count;
		__u32 tx_put, tx_get, tx_bufsize;

		tx_get = readl(&buf_ctrl->tx_get);
		tx_put = readl(&buf_ctrl->tx_put);
		tx_bufsize = readl(&buf_ctrl->tx_bufsize);
		if (tx_put >= tx_get)
			char_count = tx_put - tx_get;
		else
			char_count = tx_put - tx_get + tx_bufsize;
#ifdef CY_DEBUG_IO
		printk(KERN_DEBUG "cyc:cy_chars_in_buffer ttyC%d %d\n",
			info->line, info->xmit_cnt + char_count);
#endif
		return info->xmit_cnt + char_count;
	}
#endif				/* Z_EXT_CHARS_IN_BUFFER */
}