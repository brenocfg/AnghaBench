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
 int INTEL_PT_ERR_MAX ; 
 int INTEL_PT_ERR_UNK ; 
 int /*<<< orphan*/ * intel_pt_err_msgs ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

int intel_pt__strerror(int code, char *buf, size_t buflen)
{
	if (code < 1 || code >= INTEL_PT_ERR_MAX)
		code = INTEL_PT_ERR_UNK;
	strlcpy(buf, intel_pt_err_msgs[code], buflen);
	return 0;
}