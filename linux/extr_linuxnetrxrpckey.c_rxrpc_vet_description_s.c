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
 unsigned long simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static int rxrpc_vet_description_s(const char *desc)
{
	unsigned long num;
	char *p;

	num = simple_strtoul(desc, &p, 10);
	if (*p != ':' || num > 65535)
		return -EINVAL;
	num = simple_strtoul(p + 1, &p, 10);
	if (*p || num < 1 || num > 255)
		return -EINVAL;
	return 0;
}