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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int DER_BAD ; 

__attribute__((used)) static uint32_t
gettag(const uint8_t *c, size_t *p, size_t l)
{
	uint32_t tag;

	if (*p >= l)
		return DER_BAD;

	tag = c[(*p)++] & 0x1f;

	if (tag != 0x1f)
		return tag;

	if (*p >= l)
		return DER_BAD;

	while (c[*p] >= 0x80) {
		tag = tag * 128 + c[(*p)++] - 0x80;
		if (*p >= l)
			return DER_BAD;
	}
	return tag;
}