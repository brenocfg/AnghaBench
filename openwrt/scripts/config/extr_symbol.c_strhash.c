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

__attribute__((used)) static unsigned strhash(const char *s)
{
	/* fnv32 hash */
	unsigned hash = 2166136261U;
	for (; *s; s++)
		hash = (hash ^ *s) * 0x01000193;
	return hash;
}