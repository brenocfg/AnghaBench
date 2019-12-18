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

/* Variables and functions */
 int /*<<< orphan*/  r_bin_java_calculate_class_access_value (char const*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_cmd_java_print_class_access_flags_value( const char * flags ){
	ut16 result = r_bin_java_calculate_class_access_value (flags);
	r_cons_printf ("Access Value for %s = 0x%04x\n", flags, result);
	return true;
}