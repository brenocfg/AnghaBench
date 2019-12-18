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
 unsigned int UNICODE_MAJ_MAX ; 
 unsigned int UNICODE_MIN_MAX ; 
 unsigned int UNICODE_REV_MAX ; 

__attribute__((used)) static int age_valid(unsigned int major, unsigned int minor,
		     unsigned int revision)
{
	if (major > UNICODE_MAJ_MAX)
		return 0;
	if (minor > UNICODE_MIN_MAX)
		return 0;
	if (revision > UNICODE_REV_MAX)
		return 0;
	return 1;
}