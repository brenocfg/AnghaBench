#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  io; int /*<<< orphan*/  config; } ;
struct TYPE_5__ {int perm; } ;
typedef  TYPE_1__ RIOMap ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int R_PERM_W ; 
 scalar_t__ r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* r_io_map_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool canWrite(RCore *core, ut64 addr) {
	if (r_config_get_i (core->config, "io.cache")) {
		return true;
	}
	RIOMap *map = r_io_map_get (core->io, addr);
	return (map && (map->perm & R_PERM_W));
}