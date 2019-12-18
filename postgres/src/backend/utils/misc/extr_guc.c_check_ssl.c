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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_check_errmsg (char*) ; 

__attribute__((used)) static bool
check_ssl(bool *newval, void **extra, GucSource source)
{
#ifndef USE_SSL
	if (*newval)
	{
		GUC_check_errmsg("SSL is not supported by this build");
		return false;
	}
#endif
	return true;
}