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
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_cons_last () ; 

__attribute__((used)) static int cmd_last(void *data, const char *input) {
	switch (*input) {
	case 0:
		r_cons_last ();
		break;
	default:
		eprintf ("Usage: _  print last output\n");
	}
	return 0;
}