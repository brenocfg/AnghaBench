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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  build_window_strings (char const*,char**,char**,char**) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,char*,char*) ; 
 int /*<<< orphan*/  obs_property_list_insert_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  obs_property_list_item_disable (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void insert_preserved_val(obs_property_t *p, const char *val)
{
	char *class = NULL;
	char *title = NULL;
	char *executable = NULL;
	struct dstr desc = {0};

	build_window_strings(val, &class, &title, &executable);

	dstr_printf(&desc, "[%s]: %s", executable, title);
	obs_property_list_insert_string(p, 1, desc.array, val);
	obs_property_list_item_disable(p, 1, true);

	dstr_free(&desc);
	bfree(class);
	bfree(title);
	bfree(executable);
}