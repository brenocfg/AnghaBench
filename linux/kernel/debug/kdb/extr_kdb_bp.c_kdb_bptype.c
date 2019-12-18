#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bp_type; } ;
typedef  TYPE_1__ kdb_bp_t ;

/* Variables and functions */
 char** kdb_rwtypes ; 

__attribute__((used)) static char *kdb_bptype(kdb_bp_t *bp)
{
	if (bp->bp_type < 0 || bp->bp_type > 4)
		return "";

	return kdb_rwtypes[bp->bp_type];
}