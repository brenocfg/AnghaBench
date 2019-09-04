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
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int leaf_type; TYPE_2__ name; int /*<<< orphan*/  segment; int /*<<< orphan*/  offset; int /*<<< orphan*/  symtype; } ;
typedef  TYPE_1__ SGlobal ;

/* Variables and functions */
 int /*<<< orphan*/  READ1 (unsigned int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ2 (unsigned int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ4 (unsigned int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_scstring (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  parse_sctring (TYPE_2__*,unsigned char*,unsigned int*,int) ; 
 int /*<<< orphan*/  ut32 ; 
 int /*<<< orphan*/  ut8 ; 

__attribute__((used)) static int parse_global(char *data, int data_size, SGlobal *global) {
	unsigned int read_bytes = 2;

	READ4(read_bytes, data_size, global->symtype, data, ut32);
	READ4(read_bytes, data_size, global->offset, data, ut32);
	READ2(read_bytes, data_size, global->segment, data, ut8);
	if (global->leaf_type == 0x110E) {
		parse_sctring(&global->name, (unsigned char *)data, &read_bytes, data_size);
	} else {
		READ1(read_bytes, data_size, global->name.size, data, ut8);
		init_scstring(&global->name, global->name.size, data);
	}

	return read_bytes;
}