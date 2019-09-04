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
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  RBinJavaField ;

/* Variables and functions */
 scalar_t__ r_bin_java_get_method_code_offset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_addr_less_start (RBinJavaField *method, ut64 addr) {
	ut64 start = r_bin_java_get_method_code_offset (method);
	return (addr < start);
}