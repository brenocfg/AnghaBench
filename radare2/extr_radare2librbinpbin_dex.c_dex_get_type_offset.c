#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_7__ {int types_size; scalar_t__ types_offset; } ;
struct TYPE_9__ {TYPE_2__ header; int /*<<< orphan*/  types; } ;
struct TYPE_8__ {TYPE_1__* o; } ;
struct TYPE_6__ {scalar_t__ bin_obj; } ;
typedef  TYPE_3__ RBinFile ;
typedef  TYPE_4__ RBinDexObj ;

/* Variables and functions */

__attribute__((used)) static ut64 dex_get_type_offset(RBinFile *bf, int type_idx) {
	RBinDexObj *bin = (RBinDexObj*) bf->o->bin_obj;
	if (!bin || !bin->types) {
		return 0;
	}
	if (type_idx < 0 || type_idx >= bin->header.types_size) {
		return 0;
	}
	return bin->header.types_offset + type_idx * 0x04; //&bin->types[type_idx];
}