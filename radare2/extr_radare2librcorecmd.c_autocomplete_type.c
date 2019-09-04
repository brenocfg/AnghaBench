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
struct TYPE_2__ {int type; int /*<<< orphan*/  name; scalar_t__ desc; } ;

/* Variables and functions */
 int R_CORE_AUTOCMPLT_END ; 
 TYPE_1__* autocomplete_flags ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int autocomplete_type(const char* strflag) {
	int i;
	for (i = 0; i < R_CORE_AUTOCMPLT_END; ++i) {
		if (autocomplete_flags[i].desc && !strncmp (strflag, autocomplete_flags[i].name, 5)) {
			return autocomplete_flags[i].type;
		}
	}
	eprintf ("Invalid flag '%s'\n", strflag);
	return R_CORE_AUTOCMPLT_END;
}