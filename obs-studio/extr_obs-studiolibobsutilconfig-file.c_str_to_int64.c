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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  strtoll (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int64_t str_to_int64(const char *str)
{
	if (!str || !*str)
		return 0;

	if (str[0] == '0' && str[1] == 'x')
		return strtoll(str + 2, NULL, 16);
	else
		return strtoll(str, NULL, 10);
}