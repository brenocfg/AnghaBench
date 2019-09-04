#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int has_match ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ ,char*) ; 
 char* strdup (char const*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int exprmatch (RDebug *dbg, ut64 addr, const char *expr) {
	char *e = strdup (expr);
	if (!e) {
		return 0;
	}
	char *p = strstr (e, "..");
	ut64 a,b;
	int ret = 0;
	if (p) {
		*p = 0;
		p += 2;
		a = r_num_math (dbg->num, e);
		b = r_num_math (dbg->num, p);
		if (a<b) {
			if (addr >= a && addr <= b) {
				ret = 1;
			}
		} else {
			if (addr >= b && addr <= a) {
				ret = 1;
			}
		}
	} else {
		a = r_num_math (dbg->num, e);
		if (addr == a) {
			ret = 1;
		}
	}
	has_match = ret;
	free (e);
	return ret;
}