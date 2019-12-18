#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  bin; } ;
struct TYPE_9__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ RCoreFile ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  r_bin_cur (int /*<<< orphan*/ ) ; 
 TYPE_3__* r_bin_file_find_by_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r_bin_reload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_bin_set_env (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* r_core_file_cur (TYPE_2__*) ; 

__attribute__((used)) static int __r_core_bin_reload(RCore *r, const char *file, ut64 baseaddr) {
	int result = 0;
	RCoreFile *cf = r_core_file_cur (r);
	if (cf) {
		RBinFile *bf = r_bin_file_find_by_fd (r->bin, cf->fd);
		result = r_bin_reload (r->bin, bf->id, baseaddr);
	}
	r_core_bin_set_env (r, r_bin_cur (r->bin));
	return result;
}