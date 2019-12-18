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
 int /*<<< orphan*/  INTEL_PT_PSB_LEN ; 
 int /*<<< orphan*/  INTEL_PT_PSB_STR ; 
 unsigned char* memmem (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_pt_step_psb(unsigned char **buf, size_t *len)
{
	unsigned char *next;

	if (!*len)
		return false;

	next = memmem(*buf + 1, *len - 1, INTEL_PT_PSB_STR, INTEL_PT_PSB_LEN);
	if (next) {
		*len -= next - *buf;
		*buf = next;
		return true;
	}
	return false;
}