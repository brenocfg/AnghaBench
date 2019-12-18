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
typedef  int /*<<< orphan*/  ut64 ;
typedef  scalar_t__ st64 ;
struct TYPE_9__ {int /*<<< orphan*/  io; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ delta; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ RIOMap ;
typedef  TYPE_2__ RIODesc ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 TYPE_2__* r_io_desc_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_io_fd_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* r_io_map_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool isValidAddress (RCore *core, ut64 addr) {
	// check if address is mapped
	RIOMap* map = r_io_map_get (core->io, addr);
	if (!map) {
		return false;
	}
	st64 fdsz = (st64)r_io_fd_size (core->io, map->fd);
	if (fdsz > 0 && map->delta > fdsz) {
		return false;
	}
	// check if associated file is opened
	RIODesc *desc = r_io_desc_get (core->io, map->fd);
	if (!desc) {
		return false;
	}
	// check if current map->fd is null://
	if (!strncmp (desc->name, "null://", 7)) {
		return false;
	}
	return true;
}