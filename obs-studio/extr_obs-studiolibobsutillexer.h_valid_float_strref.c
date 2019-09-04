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
struct strref {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int valid_float_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool valid_float_strref(const struct strref *str)
{
	return valid_float_str(str->array, str->len);
}