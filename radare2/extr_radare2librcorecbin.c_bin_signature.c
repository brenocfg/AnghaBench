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
struct TYPE_6__ {char* (* signature ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  bin; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RBinPlugin ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MODE_JSON (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * r_bin_cur (int /*<<< orphan*/ ) ; 
 TYPE_2__* r_bin_file_cur_plugin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_println (char const*) ; 
 char* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bin_signature(RCore *r, int mode) {
	RBinFile *cur = r_bin_cur (r->bin);
	RBinPlugin *plg = r_bin_file_cur_plugin (cur);
	if (plg && plg->signature) {
		const char *signature = plg->signature (cur, IS_MODE_JSON (mode));
		r_cons_println (signature);
		free ((char*) signature);
		return true;
	}
	return false;
}