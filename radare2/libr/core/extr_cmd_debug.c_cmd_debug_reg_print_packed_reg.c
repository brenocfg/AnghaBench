#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  float ut64 ;
struct TYPE_9__ {TYPE_1__* dbg; } ;
struct TYPE_8__ {int packed_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RRegItem ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int NUM_INT_PACK_TYPES ; 
 int NUM_PACK_TYPES ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  pack_print (int,float,int) ; 
 int* pack_sizes ; 
 int /*<<< orphan*/  r_cons_newline () ; 
 float r_reg_get_pack (int /*<<< orphan*/ ,TYPE_2__*,int,int) ; 

__attribute__((used)) static void cmd_debug_reg_print_packed_reg(RCore *core, RRegItem *item, char explicit_size, char* pack_show)	{
	int pi, i;
	for (pi = 0; pi < NUM_PACK_TYPES; pi++) {
		if (!explicit_size || pack_show[pi]) {
			for (i = 0; i < item->packed_size / pack_sizes[pi]; i++) {
				ut64 res = r_reg_get_pack(core->dbg->reg, item, i, pack_sizes[pi]);
				if( pi > NUM_INT_PACK_TYPES-1)	{ // are we printing int or double?
					if (pack_sizes[pi] == 64)	{
						double dres;
						memcpy ((void*)&dres, (void*)&res, 8);
						pack_print (i, dres, pi);
					} else if (pack_sizes[pi] == 32) {
						float fres;
						memcpy ((void*)&fres, (void*)&res, 4);
						pack_print (i, fres, pi);
					}
				} else {
					pack_print (i, res, pi);
				}
			}
			r_cons_newline ();
		}
	}
}