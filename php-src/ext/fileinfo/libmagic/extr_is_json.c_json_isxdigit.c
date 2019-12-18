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
 scalar_t__ json_isdigit (unsigned char) ; 

__attribute__((used)) static int
json_isxdigit(unsigned char uc)
{
	if (json_isdigit(uc))
		return 1;
	switch (uc) {
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		return 1;
	default:
		return 0;
	}
}