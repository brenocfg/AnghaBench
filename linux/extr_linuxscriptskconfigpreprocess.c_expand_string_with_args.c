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
 char* __expand_string (char const**,int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  is_end_of_str ; 

__attribute__((used)) static char *expand_string_with_args(const char *in, int argc, char *argv[])
{
	return __expand_string(&in, is_end_of_str, argc, argv);
}