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
struct TYPE_3__ {char const* (* get_name ) (int /*<<< orphan*/ *,int,int,int) ;} ;
typedef  TYPE_1__ RBinPlugin ;
typedef  int /*<<< orphan*/  RBinFile ;
typedef  int /*<<< orphan*/  RBin ;

/* Variables and functions */
 int /*<<< orphan*/ * r_bin_cur (int /*<<< orphan*/ *) ; 
 TYPE_1__* r_bin_file_cur_plugin (int /*<<< orphan*/ *) ; 
 char const* stub1 (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static const char *__getname(RBin *bin, int type, int idx, bool sd) {
	RBinFile *a = r_bin_cur (bin);
	RBinPlugin *plugin = r_bin_file_cur_plugin (a);
	if (plugin && plugin->get_name) {
		return plugin->get_name (a, type, idx, sd);
	}
	return NULL;
}