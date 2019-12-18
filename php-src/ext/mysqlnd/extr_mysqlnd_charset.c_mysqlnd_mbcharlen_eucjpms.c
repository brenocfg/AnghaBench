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
 scalar_t__ valid_eucjpms (unsigned int const) ; 
 scalar_t__ valid_eucjpms_ss2 (unsigned int const) ; 
 scalar_t__ valid_eucjpms_ss3 (unsigned int const) ; 

__attribute__((used)) static unsigned int mysqlnd_mbcharlen_eucjpms(const unsigned int jpms)
{
	if (valid_eucjpms(jpms) || valid_eucjpms_ss2(jpms)) {
		return 2;
	}
	if (valid_eucjpms_ss3(jpms)) {
		return 3;
	}
	return 1;
}