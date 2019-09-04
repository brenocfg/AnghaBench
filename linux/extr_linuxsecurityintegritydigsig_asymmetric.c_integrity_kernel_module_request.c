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

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int integrity_kernel_module_request(char *kmod_name)
{
	if (strncmp(kmod_name, "crypto-pkcs1pad(rsa,", 20) == 0)
		return -EINVAL;

	return 0;
}