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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

__attribute__((used)) static void memcpy_32to16(void *dest, const void *src, size_t n)
{
	unsigned int i = 0;
	u16 *d = (u16 *)dest, *s = (u16 *)src;

	s++;
	for (i = n; i > 0; i--) {
		*d++ = *s++;
		s++;
	}
}