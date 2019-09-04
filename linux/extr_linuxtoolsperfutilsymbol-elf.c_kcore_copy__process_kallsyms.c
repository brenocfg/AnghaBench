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
typedef  scalar_t__ u64 ;
struct kcore_copy_info {scalar_t__ last_module_symbol; scalar_t__ first_symbol; scalar_t__ last_symbol; scalar_t__ etext; scalar_t__ stext; } ;

/* Variables and functions */
 scalar_t__ is_entry_trampoline (char const*) ; 
 int /*<<< orphan*/  kallsyms__is_function (char) ; 
 int /*<<< orphan*/  kcore_copy__new_sym (struct kcore_copy_info*,scalar_t__) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int kcore_copy__process_kallsyms(void *arg, const char *name, char type,
					u64 start)
{
	struct kcore_copy_info *kci = arg;

	if (!kallsyms__is_function(type))
		return 0;

	if (strchr(name, '[')) {
		if (start > kci->last_module_symbol)
			kci->last_module_symbol = start;
		return 0;
	}

	if (!kci->first_symbol || start < kci->first_symbol)
		kci->first_symbol = start;

	if (!kci->last_symbol || start > kci->last_symbol)
		kci->last_symbol = start;

	if (!strcmp(name, "_stext")) {
		kci->stext = start;
		return 0;
	}

	if (!strcmp(name, "_etext")) {
		kci->etext = start;
		return 0;
	}

	if (is_entry_trampoline(name) && !kcore_copy__new_sym(kci, start))
		return -1;

	return 0;
}