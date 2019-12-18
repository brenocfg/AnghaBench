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
 scalar_t__ TOK_LAND ; 
 int /*<<< orphan*/  expr_or () ; 
 int /*<<< orphan*/  next () ; 
 scalar_t__ tcc_nerr () ; 
 scalar_t__ tok ; 

__attribute__((used)) static void expr_land(void) {
	expr_or ();
	if (tok == TOK_LAND) {
		while (tcc_nerr () == 0) {
			if (tok != TOK_LAND) {
				break;
			}
			next ();
			expr_or ();
		}
	}
}