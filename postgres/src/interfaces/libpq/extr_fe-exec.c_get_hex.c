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
 int* hexlookup ; 

__attribute__((used)) static inline char
get_hex(char c)
{
	int			res = -1;

	if (c > 0 && c < 127)
		res = hexlookup[(unsigned char) c];

	return (char) res;
}