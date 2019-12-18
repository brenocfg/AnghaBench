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
struct strref {char const* array; int /*<<< orphan*/  len; } ;
struct cf_preprocessor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_preprocess_remove_def_strref (struct cf_preprocessor*,struct strref*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void cf_preprocessor_remove_def(struct cf_preprocessor *pp,
				const char *def_name)
{
	struct strref ref;
	ref.array = def_name;
	ref.len = strlen(def_name);
	cf_preprocess_remove_def_strref(pp, &ref);
}