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
typedef  int u8 ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ ec_read_only; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MSI_STANDARD_EC_COMMAND_ADDRESS ; 
 int ec_read (int /*<<< orphan*/ ,int*) ; 
 int ec_write (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* quirks ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t set_device_state(const char *buf, size_t count, u8 mask)
{
	int status;
	u8 wdata = 0, rdata;
	int result;

	if (sscanf(buf, "%i", &status) != 1 || (status < 0 || status > 1))
		return -EINVAL;

	if (quirks->ec_read_only)
		return -EOPNOTSUPP;

	/* read current device state */
	result = ec_read(MSI_STANDARD_EC_COMMAND_ADDRESS, &rdata);
	if (result < 0)
		return result;

	if (!!(rdata & mask) != status) {
		/* reverse device bit */
		if (rdata & mask)
			wdata = rdata & ~mask;
		else
			wdata = rdata | mask;

		result = ec_write(MSI_STANDARD_EC_COMMAND_ADDRESS, wdata);
		if (result < 0)
			return result;
	}

	return count;
}