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
 int EINVAL ; 
 scalar_t__ isdigit (char) ; 
 int kstrtol (char*,int /*<<< orphan*/ ,long*) ; 
 int kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int str_to_immediate(char *str, unsigned long *imm)
{
	if (isdigit(str[0]))
		return kstrtoul(str, 0, imm);
	else if (str[0] == '-')
		return kstrtol(str, 0, (long *)imm);
	else if (str[0] == '+')
		return kstrtol(str + 1, 0, (long *)imm);
	return -EINVAL;
}