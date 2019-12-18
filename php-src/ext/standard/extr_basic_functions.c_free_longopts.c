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
struct TYPE_3__ {char opt_char; int /*<<< orphan*/ * opt_name; } ;
typedef  TYPE_1__ opt_struct ;

/* Variables and functions */
 int /*<<< orphan*/  efree (char*) ; 

__attribute__((used)) static void free_longopts(opt_struct *longopts)
{
	opt_struct *p;

	if (longopts) {
		for (p = longopts; p && p->opt_char != '-'; p++) {
			if (p->opt_name != NULL) {
				efree((char *)(p->opt_name));
			}
		}
	}
}