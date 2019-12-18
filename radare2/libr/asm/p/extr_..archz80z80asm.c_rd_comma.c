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
 char* delspc (char const*) ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 

__attribute__((used)) static void rd_comma(const char **p) {
	*p = delspc (*p);
	if (**p != ',') {
		eprintf ("`,' expected. Remainder of line: %s\n", *p);
		return;
	}
	*p = delspc ((*p) + 1);
}