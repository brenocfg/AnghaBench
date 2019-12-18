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
typedef  int /*<<< orphan*/  RRegex ;

/* Variables and functions */
 int /*<<< orphan*/  R_REGEX_NOSUB ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int r_regex_comp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int r_regex_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_regex_free (int /*<<< orphan*/ *) ; 

int _main() {
	RRegex rx;
	int rc = r_regex_comp (&rx, "^hi", R_REGEX_NOSUB);	
	if (rc) {
		printf ("error\n");

	} else {
		rc = r_regex_exec (&rx, "patata", 0, 0, 0);
		printf ("out = %d\n", rc);

		rc = r_regex_exec (&rx, "hillow", 0, 0, 0);
		printf ("out = %d\n", rc);
	}
	r_regex_free (&rx);
	return 0;
}