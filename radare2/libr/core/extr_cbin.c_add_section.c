#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ paddr; scalar_t__ vsize; int perm; scalar_t__ name; } ;
struct TYPE_9__ {int /*<<< orphan*/  io; } ;
struct TYPE_8__ {char* name; } ;
typedef  TYPE_1__ RIOMap ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RBinSection ;

/* Variables and functions */
 int R_PERM_X ; 
 scalar_t__ UT64_ADD_OVFCHK (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  io_create_mem_map (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  r_io_desc_get (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* r_io_map_add_batch (int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__,scalar_t__) ; 
 char* r_str_newf (char*,scalar_t__) ; 
 scalar_t__ strstr (scalar_t__,char*) ; 

__attribute__((used)) static void add_section(RCore *core, RBinSection *sec, ut64 addr, int fd) {
	if (!r_io_desc_get (core->io, fd) || UT64_ADD_OVFCHK (sec->size, sec->paddr) ||
	    UT64_ADD_OVFCHK (sec->size, addr) || !sec->vsize) {
		return;
	}

	ut64 size = sec->vsize;
	// if there is some part of the section that needs to be zeroed by the loader
	// we add a null map that takes care of it
	if (sec->vsize > sec->size) {
		if (!io_create_mem_map (core->io, sec, addr + sec->size)) {
			return;
		}

		size = sec->size;
	}

	// then we map the part of the section that comes from the physical file
	char *map_name = r_str_newf ("fmap.%s", sec->name);
	if (!map_name) {
		return;
	}

	int perm = sec->perm;
	// workaround to force exec bit in text section
	if (sec->name &&  strstr (sec->name, "text")) {
		perm |= R_PERM_X;
	}

	RIOMap *map = r_io_map_add_batch (core->io, fd, perm, sec->paddr, addr, size);
	if (!map) {
		free (map_name);
		return;
	}
	map->name = map_name;
	return;
}