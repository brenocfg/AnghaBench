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
struct tty_struct {struct hvcs_struct* driver_data; } ;
struct TYPE_2__ {scalar_t__ count; } ;
struct hvcs_struct {int chars_in_buffer; TYPE_1__ port; } ;

/* Variables and functions */
 int HVCS_BUFF_LEN ; 

__attribute__((used)) static int hvcs_write_room(struct tty_struct *tty)
{
	struct hvcs_struct *hvcsd = tty->driver_data;

	if (!hvcsd || hvcsd->port.count <= 0)
		return 0;

	return HVCS_BUFF_LEN - hvcsd->chars_in_buffer;
}