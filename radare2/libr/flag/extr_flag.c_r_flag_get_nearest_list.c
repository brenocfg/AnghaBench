#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_10__ {int /*<<< orphan*/  by_off; } ;
struct TYPE_9__ {scalar_t__ off; } ;
typedef  TYPE_1__ RFlagsAtOffset ;
typedef  TYPE_2__ RFlag ;

/* Variables and functions */
 TYPE_1__* r_skiplist_get_geq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* r_skiplist_get_leq (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static RFlagsAtOffset *r_flag_get_nearest_list(RFlag *f, ut64 off, int dir) {
	RFlagsAtOffset key = { .off = off };
	RFlagsAtOffset *flags = (dir >= 0)
		? r_skiplist_get_geq (f->by_off, &key)
		: r_skiplist_get_leq (f->by_off, &key);
	return (dir == 0 && flags && flags->off != off)? NULL: flags;
}