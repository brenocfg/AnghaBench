#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rclass; } ;
struct TYPE_7__ {int /*<<< orphan*/  bin; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RBinInfo ;

/* Variables and functions */
 int /*<<< orphan*/  bin_no_resources (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bin_pe_resources (TYPE_1__*,int) ; 
 TYPE_2__* r_bin_get_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bin_resources(RCore *r, int mode) {
	const RBinInfo *info = r_bin_get_info (r->bin);
	if (!info || !info->rclass) {
		return false;
	}
	if (!strncmp ("pe", info->rclass, 2)) {
		bin_pe_resources (r, mode);
	} else {
		bin_no_resources (r, mode);
	}
	return true;
}