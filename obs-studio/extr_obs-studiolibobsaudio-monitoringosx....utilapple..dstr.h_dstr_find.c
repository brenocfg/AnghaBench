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
struct dstr {int /*<<< orphan*/  array; } ;

/* Variables and functions */
 char const* strstr (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline const char *dstr_find(const struct dstr *str, const char *find)
{
	return strstr(str->array, find);
}