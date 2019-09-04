#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; TYPE_1__* driver_data; } ;
struct TYPE_3__ {int tx_count; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sanity_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int chars_in_buffer(struct tty_struct *tty)
{
	SLMP_INFO *info = tty->driver_data;

	if (sanity_check(info, tty->name, "chars_in_buffer"))
		return 0;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s chars_in_buffer()=%d\n",
		       __FILE__, __LINE__, info->device_name, info->tx_count);

	return info->tx_count;
}