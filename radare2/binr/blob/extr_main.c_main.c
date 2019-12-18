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
typedef  int /*<<< orphan*/  RMain ;

/* Variables and functions */
 int /*<<< orphan*/  r_main_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_main_new (char*) ; 
 int r_main_run (int /*<<< orphan*/ *,int,char**) ; 

int main(int argc, char **argv) {
	int rc = 1;
	RMain *m = r_main_new (argv[0]);
	if (m) {
		rc = r_main_run (m, argc, argv);
		r_main_free (m);
	}
	return rc;
}