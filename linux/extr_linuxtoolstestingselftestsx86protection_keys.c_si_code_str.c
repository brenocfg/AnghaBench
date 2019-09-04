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
 int SEGV_ACCERR ; 
 int SEGV_BNDERR ; 
 int SEGV_MAPERR ; 
 int SEGV_PKUERR ; 

__attribute__((used)) static char *si_code_str(int si_code)
{
	if (si_code == SEGV_MAPERR)
		return "SEGV_MAPERR";
	if (si_code == SEGV_ACCERR)
		return "SEGV_ACCERR";
	if (si_code == SEGV_BNDERR)
		return "SEGV_BNDERR";
	if (si_code == SEGV_PKUERR)
		return "SEGV_PKUERR";
	return "UNKNOWN";
}