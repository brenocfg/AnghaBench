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
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static bool
is_an_int(const char *str)
{
	const char *ptr = str;

	/* skip leading spaces; cast is consistent with strtoint64 */
	while (*ptr && isspace((unsigned char) *ptr))
		ptr++;

	/* skip sign */
	if (*ptr == '+' || *ptr == '-')
		ptr++;

	/* at least one digit */
	if (*ptr && !isdigit((unsigned char) *ptr))
		return false;

	/* eat all digits */
	while (*ptr && isdigit((unsigned char) *ptr))
		ptr++;

	/* must have reached end of string */
	return *ptr == '\0';
}