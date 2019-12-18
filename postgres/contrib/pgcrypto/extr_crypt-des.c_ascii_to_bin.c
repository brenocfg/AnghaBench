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

__attribute__((used)) static inline int
ascii_to_bin(char ch)
{
	if (ch > 'z')
		return 0;
	if (ch >= 'a')
		return (ch - 'a' + 38);
	if (ch > 'Z')
		return 0;
	if (ch >= 'A')
		return (ch - 'A' + 12);
	if (ch > '9')
		return 0;
	if (ch >= '.')
		return (ch - '.');
	return 0;
}