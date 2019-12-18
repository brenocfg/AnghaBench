#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int is_key; int is_first; } ;
typedef  TYPE_1__ PJ ;

/* Variables and functions */
 int /*<<< orphan*/  pj_raw (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_return_if_fail (TYPE_1__*) ; 

__attribute__((used)) static void pj_comma(PJ *j) {
	r_return_if_fail (j);
	if (!j->is_key) {
		if (!j->is_first) {
			pj_raw (j, ",");
		}
	}
	j->is_first = false;
	j->is_key = false;
}