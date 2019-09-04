#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_11__ {TYPE_3__* bin; } ;
struct TYPE_13__ {TYPE_4__ binb; } ;
struct TYPE_12__ {scalar_t__ code_from; scalar_t__ code_to; } ;
struct TYPE_10__ {TYPE_2__* cur; } ;
struct TYPE_9__ {TYPE_1__* o; } ;
struct TYPE_8__ {scalar_t__ bin_obj; } ;
typedef  TYPE_5__ RBinDexObj ;
typedef  TYPE_6__ RAnal ;

/* Variables and functions */

__attribute__((used)) static bool is_valid_offset(RAnal *anal, ut64 addr, int hasperm) {
	RBinDexObj *bin_dex = (RBinDexObj*) anal->binb.bin->cur->o->bin_obj;
	if (!bin_dex) {
		return false;
	}
	return addr >= bin_dex->code_from && addr <= bin_dex->code_to;
}