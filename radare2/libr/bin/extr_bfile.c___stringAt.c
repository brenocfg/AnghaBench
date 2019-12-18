#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_5__ {TYPE_1__* o; } ;
struct TYPE_4__ {int /*<<< orphan*/  strings_db; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBinString ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/ * ht_up_find (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RBinString *__stringAt(RBinFile *bf, RList *ret, ut64 addr) {
	if (addr != 0 && addr != UT64_MAX) {
		return ht_up_find (bf->o->strings_db, addr, NULL);
	}
	return NULL;
}