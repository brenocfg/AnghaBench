#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 int /*<<< orphan*/ * r_debug_native_frames (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RList* r_debug_gdb_frames(RDebug *dbg, ut64 at) {
	return r_debug_native_frames (dbg, at);
}