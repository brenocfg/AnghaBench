#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* g_sections; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  last; } ;
typedef  TYPE_1__ RBinElfSection ;
typedef  TYPE_2__ ELFOBJ ;

/* Variables and functions */
 scalar_t__ ELF_STRING_LENGTH ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

__attribute__((used)) static RBinElfSection* get_section_by_name(ELFOBJ *bin, const char *section_name) {
	int i;
	if (bin->g_sections) {
		for (i = 0; !bin->g_sections[i].last; i++) {
			if (!strncmp (bin->g_sections[i].name, section_name, ELF_STRING_LENGTH - 1)) {
				return &bin->g_sections[i];
			}
		}
	}
	return NULL;
}