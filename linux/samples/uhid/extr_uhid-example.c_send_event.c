#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int* data; } ;
struct TYPE_4__ {TYPE_1__ input; } ;
struct uhid_event {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  UHID_INPUT ; 
 int abs_hor ; 
 int abs_ver ; 
 scalar_t__ btn1_down ; 
 scalar_t__ btn2_down ; 
 scalar_t__ btn3_down ; 
 int /*<<< orphan*/  memset (struct uhid_event*,int /*<<< orphan*/ ,int) ; 
 int uhid_write (int,struct uhid_event*) ; 
 int wheel ; 

__attribute__((used)) static int send_event(int fd)
{
	struct uhid_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.type = UHID_INPUT;
	ev.u.input.size = 5;

	ev.u.input.data[0] = 0x1;
	if (btn1_down)
		ev.u.input.data[1] |= 0x1;
	if (btn2_down)
		ev.u.input.data[1] |= 0x2;
	if (btn3_down)
		ev.u.input.data[1] |= 0x4;

	ev.u.input.data[2] = abs_hor;
	ev.u.input.data[3] = abs_ver;
	ev.u.input.data[4] = wheel;

	return uhid_write(fd, &ev);
}