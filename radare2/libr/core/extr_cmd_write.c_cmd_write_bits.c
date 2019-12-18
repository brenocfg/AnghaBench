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
typedef  int ut64 ;
typedef  int /*<<< orphan*/  ret ;
typedef  int /*<<< orphan*/  orig ;
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  io; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_write_fail (TYPE_1__*) ; 
 int /*<<< orphan*/  r_core_write_at (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_io_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cmd_write_bits(RCore *core, int set, ut64 val) {
	ut64 ret, orig;
	// used to set/unset bit in current address
	r_io_read_at (core->io, core->offset, (ut8*)&orig, sizeof (orig));
	if (set) {
		ret = orig | val;
	} else {
		ret = orig & (~(val));
	}
	if (!r_core_write_at (core, core->offset, (const ut8*)&ret, sizeof (ret))) {
		cmd_write_fail (core);
	}
}