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
 int MTS64_CTL_STROBE ; 
 int MTS64_CTL_WRITE_DATA ; 
 int /*<<< orphan*/  mts64_device_ready (struct parport*) ; 
 int /*<<< orphan*/  parport_write_control (struct parport*,int) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mts64_write_data(struct parport *p, u8 c)
{
	mts64_device_ready(p);

	parport_write_data(p, c);

	parport_write_control(p, MTS64_CTL_WRITE_DATA);
	parport_write_control(p, MTS64_CTL_WRITE_DATA | MTS64_CTL_STROBE);
	parport_write_control(p, MTS64_CTL_WRITE_DATA);
}