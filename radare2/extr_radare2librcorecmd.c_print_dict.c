#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; char* name; } ;
struct TYPE_4__ {int n_subcmds; scalar_t__ type; struct TYPE_4__** subcmds; int /*<<< orphan*/  cmd; scalar_t__ locked; } ;
typedef  TYPE_1__ RCoreAutocomplete ;

/* Variables and functions */
 int R_CORE_AUTOCMPLT_END ; 
 TYPE_3__* autocomplete_flags ; 
 int /*<<< orphan*/  eprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void print_dict(RCoreAutocomplete* a, int sub) {
	if (!a) {
		return;
	}
	int i, j;
	const char* name = "unknown";
	for (i = 0; i < a->n_subcmds; ++i) {
		RCoreAutocomplete* b = a->subcmds[i];
		if (b->locked) {
			continue;
		}
		for (j = 0; j < R_CORE_AUTOCMPLT_END; ++j) {
			if (b->type == autocomplete_flags[j].type) {
				name = autocomplete_flags[j].name;
				break;
			}
		}
		eprintf ("[%3d] %s: '%s'\n", sub, name, b->cmd);
		print_dict (a->subcmds[i], sub + 1);
	}
}