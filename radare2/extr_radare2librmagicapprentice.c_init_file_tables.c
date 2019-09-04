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
struct type_tbl_s {size_t type; int /*<<< orphan*/  format; int /*<<< orphan*/  name; scalar_t__ len; } ;

/* Variables and functions */
 size_t FILE_NAMES_SIZE ; 
 int /*<<< orphan*/ * magic_file_formats ; 
 int /*<<< orphan*/ * magic_file_names ; 
 struct type_tbl_s* type_tbl ; 

__attribute__((used)) static void init_file_tables(void) {
	static int done = 0;
	const struct type_tbl_s *p;
	if (done) {
		return;
	}
	done++;
	for (p = type_tbl; p->len; p++) {
		if (p->type >= FILE_NAMES_SIZE) {
			continue;
		}
		magic_file_names[p->type] = p->name;
		magic_file_formats[p->type] = p->format;
	}
}