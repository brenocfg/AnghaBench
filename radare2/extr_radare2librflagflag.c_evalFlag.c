#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  num; } ;
struct TYPE_6__ {scalar_t__ alias; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ RFlagItem ;
typedef  TYPE_2__ RFlag ;

/* Variables and functions */
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RFlagItem *evalFlag(RFlag *f, RFlagItem *item) {
	r_return_val_if_fail (f && item, NULL);
	if (item->alias) {
		item->offset = r_num_math (f->num, item->alias);
	}
	return item;
}