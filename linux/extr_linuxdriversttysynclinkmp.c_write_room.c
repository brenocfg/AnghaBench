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
struct TYPE_5__ {int max_frame_size; int tx_count; int /*<<< orphan*/  device_name; scalar_t__ tx_active; TYPE_1__ params; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int HDLC_MAX_FRAME_SIZE ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sanity_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int write_room(struct tty_struct *tty)
{
	SLMP_INFO *info = tty->driver_data;
	int ret;

	if (sanity_check(info, tty->name, "write_room"))
		return 0;

	if (info->params.mode == MGSL_MODE_HDLC) {
		ret = (info->tx_active) ? 0 : HDLC_MAX_FRAME_SIZE;
	} else {
		ret = info->max_frame_size - info->tx_count - 1;
		if (ret < 0)
			ret = 0;
	}

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s write_room()=%d\n",
		       __FILE__, __LINE__, info->device_name, ret);

	return ret;
}