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
 int /*<<< orphan*/  free (char*) ; 
 char* r_bin_java_resolve_b64_encode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 

__attribute__((used)) static int r_cmd_java_resolve_cp_idx_b64 (RBinJavaObj *obj, ut16 idx) {
	if (obj && idx){
		char * str = r_bin_java_resolve_b64_encode (obj, idx) ;
		r_cons_println (str);
		free (str);
	}
	return true;
}