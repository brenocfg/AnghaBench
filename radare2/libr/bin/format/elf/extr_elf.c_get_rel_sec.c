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
typedef  int /*<<< orphan*/  RBinElfSection ;
typedef  int /*<<< orphan*/  ELFOBJ ;

/* Variables and functions */
 int /*<<< orphan*/ * get_section_by_name (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static RBinElfSection *get_rel_sec(ELFOBJ *bin, const char **sects) {
	RBinElfSection *rel_sec = NULL;
	int j = 0;
	while (!rel_sec && sects[j]) {
		rel_sec = get_section_by_name (bin, sects[j++]);
	}
	return rel_sec;
}