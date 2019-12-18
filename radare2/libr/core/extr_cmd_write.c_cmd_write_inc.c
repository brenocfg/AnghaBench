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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  ut16 ;
typedef  int /*<<< orphan*/  st64 ;
struct TYPE_5__ {scalar_t__ block; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_write_fail (TYPE_1__*) ; 
 int /*<<< orphan*/  r_core_write_at (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void cmd_write_inc(RCore *core, int size, st64 num) {
	ut64 *v64;
	ut32 *v32;
	ut16 *v16;
	ut8 *v8;
	switch (size) {
	case 1: v8 = (ut8*)core->block; *v8 += num; break;
	case 2: v16 = (ut16*)core->block; *v16 += num; break;
	case 4: v32 = (ut32*)core->block; *v32 += num; break;
	case 8: v64 = (ut64*)core->block; *v64 += num; break;
	}
	// TODO: obey endian here
	if (!r_core_write_at (core, core->offset, core->block, size)) {
		cmd_write_fail (core);
	}
}