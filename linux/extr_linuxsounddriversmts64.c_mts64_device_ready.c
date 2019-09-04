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
typedef  int /*<<< orphan*/  u8 ;
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTS64_STAT_BSY ; 
 int /*<<< orphan*/  parport_read_status (struct parport*) ; 

__attribute__((used)) static int mts64_device_ready(struct parport *p)
{
	int i;
	u8 c;

	for (i = 0; i < 0xffff; ++i) {
		c = parport_read_status(p);
		c &= MTS64_STAT_BSY;
		if (c != 0) 
			return 1;
	} 

	return 0;
}