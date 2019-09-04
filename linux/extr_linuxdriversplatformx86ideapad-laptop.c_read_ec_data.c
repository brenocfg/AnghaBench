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
typedef  int /*<<< orphan*/  acpi_handle ;
typedef  int HZ ;

/* Variables and functions */
 scalar_t__* IDEAPAD_EC_TIMEOUT ; 
 int jiffies ; 
 scalar_t__ method_vpcr (int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ method_vpcw (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int read_ec_data(acpi_handle handle, int cmd, unsigned long *data)
{
	int val;
	unsigned long int end_jiffies;

	if (method_vpcw(handle, 1, cmd))
		return -1;

	for (end_jiffies = jiffies+(HZ)*IDEAPAD_EC_TIMEOUT/1000+1;
	     time_before(jiffies, end_jiffies);) {
		schedule();
		if (method_vpcr(handle, 1, &val))
			return -1;
		if (val == 0) {
			if (method_vpcr(handle, 0, &val))
				return -1;
			*data = val;
			return 0;
		}
	}
	pr_err("timeout in read_ec_cmd\n");
	return -1;
}