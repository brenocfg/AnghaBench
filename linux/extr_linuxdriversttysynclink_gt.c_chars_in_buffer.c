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
struct tty_struct {int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct slgt_info {int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int tbuf_bytes (struct slgt_info*) ; 

__attribute__((used)) static int chars_in_buffer(struct tty_struct *tty)
{
	struct slgt_info *info = tty->driver_data;
	int count;
	if (sanity_check(info, tty->name, "chars_in_buffer"))
		return 0;
	count = tbuf_bytes(info);
	DBGINFO(("%s chars_in_buffer()=%d\n", info->device_name, count));
	return count;
}