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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 char* sdb_json_indent (char*,char*) ; 
 char* stdin_slurp (int*) ; 

__attribute__((used)) static int jsonIndent() {
	int len;
	char *out;
	char *in = stdin_slurp (&len);
	if (!in) {
		return 0;
	}
	out = sdb_json_indent (in, "  ");
	if (!out) {
		free (in);
		return 1;
	}
	puts (out);
	free (out);
	free (in);
	return 0;
}