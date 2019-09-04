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
 int /*<<< orphan*/  isprint (char) ; 
 int /*<<< orphan*/  isspace (char) ; 

int is_printable_array(char *p, unsigned int len)
{
	unsigned int i;

	if (!p || !len || p[len - 1] != 0)
		return 0;

	len--;

	for (i = 0; i < len; i++) {
		if (!isprint(p[i]) && !isspace(p[i]))
			return 0;
	}
	return 1;
}