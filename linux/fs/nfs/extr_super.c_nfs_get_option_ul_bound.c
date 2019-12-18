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
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 int ERANGE ; 
 int nfs_get_option_ul (int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static int nfs_get_option_ul_bound(substring_t args[], unsigned long *option,
		unsigned long l_bound, unsigned long u_bound)
{
	int ret;

	ret = nfs_get_option_ul(args, option);
	if (ret != 0)
		return ret;
	if (*option < l_bound || *option > u_bound)
		return -ERANGE;
	return 0;
}