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
struct tty_struct {scalar_t__ driver_data; } ;
struct raw3215_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAW3215_THROTTLED ; 

__attribute__((used)) static void tty3215_throttle(struct tty_struct * tty)
{
	struct raw3215_info *raw;

	raw = (struct raw3215_info *) tty->driver_data;
	raw->flags |= RAW3215_THROTTLED;
}