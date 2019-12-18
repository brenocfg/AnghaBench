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
struct branch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static unsigned char *intel_bts_find_overlap(unsigned char *buf_a, size_t len_a,
					     unsigned char *buf_b, size_t len_b)
{
	size_t offs, len;

	if (len_a > len_b)
		offs = len_a - len_b;
	else
		offs = 0;

	for (; offs < len_a; offs += sizeof(struct branch)) {
		len = len_a - offs;
		if (!memcmp(buf_a + offs, buf_b, len))
			return buf_b + len;
	}

	return buf_b;
}