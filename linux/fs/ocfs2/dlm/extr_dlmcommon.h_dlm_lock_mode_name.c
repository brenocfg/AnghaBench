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
#define  LKM_EXMODE 130 
#define  LKM_NLMODE 129 
#define  LKM_PRMODE 128 

__attribute__((used)) static inline const char * dlm_lock_mode_name(int mode)
{
	switch (mode) {
		case LKM_EXMODE:
			return "EX";
		case LKM_PRMODE:
			return "PR";
		case LKM_NLMODE:
			return "NL";
	}
	return "UNKNOWN";
}