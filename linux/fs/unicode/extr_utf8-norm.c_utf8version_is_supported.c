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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int UNICODE_AGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int* utf8agetab ; 

int utf8version_is_supported(u8 maj, u8 min, u8 rev)
{
	int i = ARRAY_SIZE(utf8agetab) - 1;
	unsigned int sb_utf8version = UNICODE_AGE(maj, min, rev);

	while (i >= 0 && utf8agetab[i] != 0) {
		if (sb_utf8version == utf8agetab[i])
			return 1;
		i--;
	}
	return 0;
}