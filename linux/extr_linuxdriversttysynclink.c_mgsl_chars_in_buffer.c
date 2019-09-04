#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; struct mgsl_struct* driver_data; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct mgsl_struct {int xmit_cnt; int max_frame_size; scalar_t__ tx_active; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ MGSL_MODE_RAW ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int mgsl_chars_in_buffer(struct tty_struct *tty)
{
	struct mgsl_struct *info = tty->driver_data;
			 
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_chars_in_buffer(%s)\n",
			 __FILE__,__LINE__, info->device_name );
			 
	if (mgsl_paranoia_check(info, tty->name, "mgsl_chars_in_buffer"))
		return 0;
		
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_chars_in_buffer(%s)=%d\n",
			 __FILE__,__LINE__, info->device_name,info->xmit_cnt );
			 
	if ( info->params.mode == MGSL_MODE_HDLC ||
		info->params.mode == MGSL_MODE_RAW ) {
		/* operating in synchronous (frame oriented) mode */
		if ( info->tx_active )
			return info->max_frame_size;
		else
			return 0;
	}
			 
	return info->xmit_cnt;
}