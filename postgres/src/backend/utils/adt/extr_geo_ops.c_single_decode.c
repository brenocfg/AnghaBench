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
typedef  int /*<<< orphan*/  float8 ;

/* Variables and functions */
 int /*<<< orphan*/  float8in_internal (char*,char**,char const*,char const*) ; 

__attribute__((used)) static float8
single_decode(char *num, char **endptr_p,
			  const char *type_name, const char *orig_string)
{
	return float8in_internal(num, endptr_p, type_name, orig_string);
}