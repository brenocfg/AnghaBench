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
 int strspn (char const*,char*) ; 

__attribute__((used)) static int
ISO8601IntegerWidth(const char *fieldstart)
{
	/* We might have had a leading '-' */
	if (*fieldstart == '-')
		fieldstart++;
	return strspn(fieldstart, "0123456789");
}