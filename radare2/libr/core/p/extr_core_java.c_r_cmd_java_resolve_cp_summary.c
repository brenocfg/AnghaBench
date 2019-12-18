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
typedef  scalar_t__ ut16 ;
typedef  int /*<<< orphan*/  RBinJavaObj ;

/* Variables and functions */
 int /*<<< orphan*/  r_bin_java_resolve_cp_idx_print_summary (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int r_cmd_java_resolve_cp_summary (RBinJavaObj *obj, ut16 idx) {
	if (obj && idx){
		r_bin_java_resolve_cp_idx_print_summary (obj, idx) ;
	}
	return true;
}