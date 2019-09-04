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
struct uhid_event {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  UHID_DESTROY ; 
 int /*<<< orphan*/  memset (struct uhid_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uhid_write (int,struct uhid_event*) ; 

__attribute__((used)) static void destroy(int fd)
{
	struct uhid_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.type = UHID_DESTROY;

	uhid_write(fd, &ev);
}