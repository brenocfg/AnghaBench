#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; TYPE_2__* driver_data; } ;
struct TYPE_4__ {scalar_t__ mode; } ;
struct TYPE_5__ {unsigned char* tx_buf; int tx_count; int max_frame_size; int tx_put; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_active; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ sanity_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int put_char(struct tty_struct *tty, unsigned char ch)
{
	SLMP_INFO *info = tty->driver_data;
	unsigned long flags;
	int ret = 0;

	if ( debug_level >= DEBUG_LEVEL_INFO ) {
		printk( "%s(%d):%s put_char(%d)\n",
			__FILE__,__LINE__,info->device_name,ch);
	}

	if (sanity_check(info, tty->name, "put_char"))
		return 0;

	if (!info->tx_buf)
		return 0;

	spin_lock_irqsave(&info->lock,flags);

	if ( (info->params.mode != MGSL_MODE_HDLC) ||
	     !info->tx_active ) {

		if (info->tx_count < info->max_frame_size - 1) {
			info->tx_buf[info->tx_put++] = ch;
			if (info->tx_put >= info->max_frame_size)
				info->tx_put -= info->max_frame_size;
			info->tx_count++;
			ret = 1;
		}
	}

	spin_unlock_irqrestore(&info->lock,flags);
	return ret;
}