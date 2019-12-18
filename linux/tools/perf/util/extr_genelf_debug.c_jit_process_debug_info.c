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
typedef  scalar_t__ uint64_t ;
struct debug_entry {scalar_t__ addr; } ;
struct buffer_ext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_compilation_unit (struct buffer_ext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_debug_abbrev (struct buffer_ext*) ; 
 int /*<<< orphan*/  add_debug_line (struct buffer_ext*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_ext_dump (struct buffer_ext*,char*) ; 
 int /*<<< orphan*/  buffer_ext_size (struct buffer_ext*) ; 
 struct debug_entry* debug_entry_next (struct debug_entry*) ; 

__attribute__((used)) static int
jit_process_debug_info(uint64_t code_addr,
		       void *debug, int nr_debug_entries,
		       struct buffer_ext *dl,
		       struct buffer_ext *da,
		       struct buffer_ext *di)
{
	struct debug_entry *ent = debug;
	int i;

	for (i = 0; i < nr_debug_entries; i++) {
		ent->addr = ent->addr - code_addr;
		ent = debug_entry_next(ent);
	}
	add_compilation_unit(di, buffer_ext_size(dl));
	add_debug_line(dl, debug, nr_debug_entries, 0);
	add_debug_abbrev(da);
	if (0) buffer_ext_dump(da, "abbrev");

	return 0;
}