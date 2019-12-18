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
struct dstr {char* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,char const*,int) ; 
 int /*<<< orphan*/ * obs_source_get_filter_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *get_new_filter_name(obs_source_t *dst, const char *name)
{
	struct dstr new_name = {0};
	int inc = 0;

	dstr_copy(&new_name, name);

	for (;;) {
		obs_source_t *existing_filter =
			obs_source_get_filter_by_name(dst, new_name.array);
		if (!existing_filter)
			break;

		obs_source_release(existing_filter);

		dstr_printf(&new_name, "%s %d", name, ++inc + 1);
	}

	return new_name.array;
}