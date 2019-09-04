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
 size_t INTEL_PT_PSB_LEN ; 
 char* INTEL_PT_PSB_STR ; 
 int /*<<< orphan*/  memcmp (unsigned char*,char const*,size_t) ; 
 unsigned char* memrchr (unsigned char*,char const,size_t) ; 

__attribute__((used)) static unsigned char *intel_pt_last_psb(unsigned char *buf, size_t len)
{
	const char *n = INTEL_PT_PSB_STR;
	unsigned char *p;
	size_t k;

	if (len < INTEL_PT_PSB_LEN)
		return NULL;

	k = len - INTEL_PT_PSB_LEN + 1;
	while (1) {
		p = memrchr(buf, n[0], k);
		if (!p)
			return NULL;
		if (!memcmp(p + 1, n + 1, INTEL_PT_PSB_LEN - 1))
			return p;
		k = p - buf;
		if (!k)
			return NULL;
	}
}