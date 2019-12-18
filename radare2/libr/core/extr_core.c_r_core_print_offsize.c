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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int size; } ;
typedef  TYPE_1__ RFlagItem ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 TYPE_1__* r_flag_get_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_core_print_offsize(void *p, ut64 addr) {
	RCore *c = (RCore*)p;
	RFlagItem *item = r_flag_get_i (c->flags, addr);
	return item ? item->size: -1;
}