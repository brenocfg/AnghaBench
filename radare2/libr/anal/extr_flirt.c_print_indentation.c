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
struct TYPE_3__ {int /*<<< orphan*/  (* cb_printf ) (char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  r_str_pad (char,int) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_indentation(const RAnal *anal, int indent) {
	anal->cb_printf ("%s", r_str_pad (' ', indent));
}