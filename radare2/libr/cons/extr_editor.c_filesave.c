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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int bytes ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 char* lines ; 
 int /*<<< orphan*/  nlines ; 
 scalar_t__ path ; 
 scalar_t__ r_file_dump (scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_split (char*,char) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void filesave() {
	char buf[128];
	int i;
	if (!path) {
		eprintf ("File: ");
		buf[0] = 0;
		if (fgets (buf, sizeof (buf) - 1, stdin)) {
			buf[sizeof (buf) - 1] = 0;
			i = strlen (buf);
			if (i > 0) {
				buf[i - 1] = 0;
				free (path);
				path = strdup (buf);
			}
		}
	}
	if (lines) {
		for (i = 0; i < bytes; i++) {
			if (lines[i] == '\0') {
				lines[i] = '\n';
			}
		}
	}
	if (r_file_dump (path, (const ut8 *)lines, bytes, 0)) {
		eprintf ("File '%s' saved (%d byte(s))\n", path, bytes);
	} else {
		eprintf ("Cannot save file\n");
	}
	nlines = r_str_split (lines, '\n');
}