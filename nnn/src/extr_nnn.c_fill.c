#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regex_t ;
struct TYPE_4__ {char const* str; int /*<<< orphan*/ * regex; } ;
typedef  TYPE_1__ fltrexp_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_3__* dents ; 
 scalar_t__ filterfn (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ndents ; 
 int /*<<< orphan*/  swap_ent (int,int) ; 

__attribute__((used)) static int fill(const char *fltr, regex_t *re)
{
	int count = 0;
	fltrexp_t fltrexp = { .regex = re, .str = fltr };

	for (; count < ndents; ++count) {
		if (filterfn(&fltrexp, dents[count].name) == 0) {
			if (count != --ndents) {
				swap_ent(count, ndents);
				--count;
			}

			continue;
		}
	}

	return ndents;
}