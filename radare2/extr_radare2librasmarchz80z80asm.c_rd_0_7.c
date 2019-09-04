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
 char const* bitsetres ; 
 char* delspc (char const*) ; 
 int /*<<< orphan*/  skipword (char const**,char) ; 

__attribute__((used)) static int rd_0_7(const char **p) {
	*p = delspc (*p);
	if (**p == 0) {
		return 0;
	}
	bitsetres = *p;
	skipword (p, ',');
	return 1;
}