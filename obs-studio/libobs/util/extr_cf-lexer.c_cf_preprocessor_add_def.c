#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dstr {int /*<<< orphan*/  array; } ;
struct cf_preprocessor {int /*<<< orphan*/  defines; } ;
struct TYPE_2__ {int /*<<< orphan*/  str; } ;
struct cf_def {TYPE_1__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_addwarning (struct cf_preprocessor*,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_def_free (struct cf_def*) ; 
 struct cf_def* cf_preprocess_get_def (struct cf_preprocessor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct cf_def*) ; 
 int /*<<< orphan*/  dstr_init_copy_strref (struct dstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct cf_def*,struct cf_def*,int) ; 

void cf_preprocessor_add_def(struct cf_preprocessor *pp, struct cf_def *def)
{
	struct cf_def *existing = cf_preprocess_get_def(pp, &def->name.str);

	if (existing) {
		struct dstr name;
		dstr_init_copy_strref(&name, &def->name.str);
		cf_addwarning(pp, &def->name, "Token $1 already defined",
			      name.array, NULL, NULL);
		cf_addwarning(pp, &existing->name,
			      "Previous definition of $1 is here", name.array,
			      NULL, NULL);

		cf_def_free(existing);
		memcpy(existing, def, sizeof(struct cf_def));
	} else {
		da_push_back(pp->defines, def);
	}
}