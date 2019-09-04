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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* r_cons_input (char*) ; 
 int /*<<< orphan*/  r_core_cmdf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int writeValueCb(void *user) {
	RCore *core = (RCore *)user;
	char *res = r_cons_input ("insert number: ");
	if (res) {
		r_core_cmdf (core, "\"wv %s\"", res);
		free (res);
	}
	return 0;
}