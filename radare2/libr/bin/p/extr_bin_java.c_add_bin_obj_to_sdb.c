#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  AllJavaBinObjs; } ;
typedef  TYPE_1__ RBinJavaObj ;

/* Variables and functions */
 int /*<<< orphan*/  DB ; 
 int /*<<< orphan*/  add_sdb_bin_obj (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_bin_java_build_obj_key (TYPE_1__*) ; 

__attribute__((used)) static void add_bin_obj_to_sdb(RBinJavaObj *bin) {
	if (!bin) {
		return;
	}
	char *jvcname = r_bin_java_build_obj_key (bin);
	add_sdb_bin_obj (jvcname, bin);
	bin->AllJavaBinObjs = DB;
	free (jvcname);
}