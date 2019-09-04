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
struct intel_pt_decoder {unsigned char* buf; size_t len; } ;

/* Variables and functions */
 int INTEL_PT_PSB_LEN ; 
 int /*<<< orphan*/  INTEL_PT_PSB_STR ; 
 int /*<<< orphan*/  memcmp (unsigned char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int intel_pt_part_psb(struct intel_pt_decoder *decoder)
{
	const unsigned char *end = decoder->buf + decoder->len;
	size_t i;

	for (i = INTEL_PT_PSB_LEN - 1; i; i--) {
		if (i > decoder->len)
			continue;
		if (!memcmp(end - i, INTEL_PT_PSB_STR, i))
			return i;
	}
	return 0;
}