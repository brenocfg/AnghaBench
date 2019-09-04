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
typedef  int /*<<< orphan*/  ut64 ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_START ; 
 int /*<<< orphan*/  r_java_new_method () ; 

__attribute__((used)) static int java_new_method (ut64 method_start) {
	METHOD_START = method_start;
	// reset the current bytes consumed counter
	r_java_new_method ();
	return 0;
}