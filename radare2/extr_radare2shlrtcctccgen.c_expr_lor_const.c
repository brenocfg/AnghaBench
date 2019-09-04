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

/* Variables and functions */
 scalar_t__ TOK_LOR ; 
 int /*<<< orphan*/  expr_land_const () ; 
 int /*<<< orphan*/  next () ; 
 scalar_t__ tok ; 

__attribute__((used)) static void expr_lor_const(void) {
	expr_land_const ();
	while (tok == TOK_LOR) {
		next ();
		expr_land_const ();
	}
}