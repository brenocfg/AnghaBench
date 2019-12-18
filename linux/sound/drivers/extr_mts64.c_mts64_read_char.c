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
typedef  int u8 ;
struct parport {int dummy; } ;

/* Variables and functions */
 int MTS64_STAT_BIT_SET ; 
 int parport_read_status (struct parport*) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,int) ; 

__attribute__((used)) static u8 mts64_read_char(struct parport *p)
{
	u8 c = 0;
	u8 status;
	u8 i;

	for (i = 0; i < 8; ++i) {
		parport_write_data(p, i);
		c >>= 1;
		status = parport_read_status(p);
		if (status & MTS64_STAT_BIT_SET) 
			c |= 0x80;
	}
	
	return c;
}