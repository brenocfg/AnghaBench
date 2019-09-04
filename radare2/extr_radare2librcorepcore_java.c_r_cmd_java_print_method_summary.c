#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ut16 ;
typedef  int /*<<< orphan*/  RBinJavaObj ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ) ; 
 int r_bin_java_print_method_idx_summary (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_cmd_java_print_method_summary (RBinJavaObj *obj, ut16 idx) {
	int res = r_bin_java_print_method_idx_summary (obj, idx);
	if (res == false) {
		eprintf ("Error: Field or Method @ index (%d) not found in the RBinJavaObj.\n", idx);
		res = true;
	}
	return res;
}