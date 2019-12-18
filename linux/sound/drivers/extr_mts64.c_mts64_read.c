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
typedef  int u16 ;
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mts64_device_ready (struct parport*) ; 
 int /*<<< orphan*/  mts64_disable_readout (struct parport*) ; 
 int /*<<< orphan*/  mts64_enable_readout (struct parport*) ; 
 int mts64_read_char (struct parport*) ; 
 int parport_read_status (struct parport*) ; 

__attribute__((used)) static u16 mts64_read(struct parport *p)
{
	u8 data, status;

	mts64_device_ready(p);
	mts64_enable_readout(p);
	status = parport_read_status(p);
	data = mts64_read_char(p);
	mts64_disable_readout(p);

	return (status << 8) | data;
}