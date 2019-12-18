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
struct cf_preprocessor {int /*<<< orphan*/  sys_include_dirs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstrdup (char const*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
cf_preprocessor_add_sys_include_dir(struct cf_preprocessor *pp,
				    const char *include_dir)
{
	if (include_dir)
		da_push_back(pp->sys_include_dirs, bstrdup(include_dir));
}