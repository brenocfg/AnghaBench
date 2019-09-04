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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char*,...) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ r_str_startswith (char*,char*) ; 
 int sscanf (char*,char*,char*,int*,int*,int*,int*,char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int gdb_to_r2_profile(char *gdb) {
	char *ptr = gdb, *ptr1, *gptr, *gptr1;
	char name[16], groups[128], type[16];
	const int all = 1, gpr = 2, save = 4, restore = 8, float_ = 16,
		  sse = 32, vector = 64, system = 128, mmx = 256;
	int number, rel, offset, size, type_bits, ret;
	// Every line is -
	// Name Number Rel Offset Size Type Groups

	// Skip whitespace at beginning of line and empty lines
	while (isspace ((ut8)*ptr)) {
		ptr++;
	}
	// It's possible someone includes the heading line too. Skip it
	if (r_str_startswith (ptr, "Name")) {
		if (!(ptr = strchr (ptr, '\n'))) {
			return false;
		}
		ptr++;
	}
	for (;;) {
		// Skip whitespace at beginning of line and empty lines
		while (isspace ((ut8)*ptr)) {
			ptr++;
		}
		if (!*ptr) {
			break;
		}
		if ((ptr1 = strchr (ptr, '\n'))) {
			*ptr1 = '\0';
		}
		ret = sscanf (ptr, " %s %d %d %d %d %s %s", name, &number, &rel,
			&offset, &size, type, groups);
		// Groups is optional, others not
		if (ret < 6) {
			eprintf ("Could not parse line: %s\n", ptr);
			if (!ptr1) {
				return true;
			}
			ptr = ptr1 + 1;
			continue;
		}
		// If name is '', then skip
		if (r_str_startswith (name, "''")) {
			if (!ptr1) {
				return true;
			}
			ptr = ptr1 + 1;
			continue;
		}
		// If size is 0, skip
		if (size == 0) {
			if (!ptr1) {
				return true;
			}
			ptr = ptr1 + 1;
			continue;
		}
		// Parse group
		gptr = groups;
		type_bits = 0;
		while (1) {
			if ((gptr1 = strchr (gptr, ','))) {
				*gptr1 = '\0';
			}
			if (r_str_startswith (gptr, "general")) {
				type_bits |= gpr;
			} else if (r_str_startswith (gptr, "all")) {
				type_bits |= all;
			} else if (r_str_startswith (gptr, "save")) {
				type_bits |= save;
			} else if (r_str_startswith (gptr, "restore")) {
				type_bits |= restore;
			} else if (r_str_startswith (gptr, "float")) {
				type_bits |= float_;
			} else if (r_str_startswith (gptr, "sse")) {
				type_bits |= sse;
			} else if (r_str_startswith (gptr, "mmx")) {
				type_bits |= mmx;
			} else if (r_str_startswith (gptr, "vector")) {
				type_bits |= vector;
			} else if (r_str_startswith (gptr, "system")) {
				type_bits |= system;
			}
			if (!gptr1) {
				break;
			}
			gptr = gptr1 + 1;
		}
		// If type is not defined, skip
		if (!*type) {
			if (!ptr1) {
				return true;
			}
			ptr = ptr1 + 1;
			continue;
		}
		// TODO: More mappings between gdb and r2 reg groups. For now, either fpu or gpr
		if (!(type_bits & sse) && !(type_bits & float_)) {
			type_bits |= gpr;
		}
		// Print line
		eprintf ("%s\t%s\t.%d\t%d\t0\n",
			// Ref: Comment above about more register type mappings
			((type_bits & mmx) || (type_bits & float_) || (type_bits & sse)) ? "fpu" : "gpr",
			name, size * 8, offset);
		// Go to next line
		if (!ptr1) {
			return true;
		}
		ptr = ptr1 + 1;
		continue;
	}
	return true;
}