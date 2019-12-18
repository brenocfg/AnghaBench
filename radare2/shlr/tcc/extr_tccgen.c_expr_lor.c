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
 int /*<<< orphan*/  expr_land () ; 
 int /*<<< orphan*/  next () ; 
 scalar_t__ tcc_nerr () ; 
 scalar_t__ tok ; 

__attribute__((used)) static void expr_lor(void) {
	expr_land ();
	if (tok == TOK_LOR) {
		while (tcc_nerr () == 0) {
			if (tok != TOK_LOR) {
				break;
			}
			next ();
			expr_land ();
		}
	}
}