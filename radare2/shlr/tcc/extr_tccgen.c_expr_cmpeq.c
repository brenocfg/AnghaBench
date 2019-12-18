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
 scalar_t__ TOK_EQ ; 
 scalar_t__ TOK_NE ; 
 int /*<<< orphan*/  expr_cmp () ; 
 int /*<<< orphan*/  next () ; 
 scalar_t__ tok ; 

__attribute__((used)) static void expr_cmpeq(void) {
	expr_cmp ();
	while (tok == TOK_EQ || tok == TOK_NE) {
		next ();
		expr_cmp ();
	}
}