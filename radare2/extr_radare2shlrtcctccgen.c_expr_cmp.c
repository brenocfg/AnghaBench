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
 scalar_t__ TOK_GT ; 
 scalar_t__ TOK_UGE ; 
 scalar_t__ TOK_ULE ; 
 scalar_t__ TOK_ULT ; 
 int /*<<< orphan*/  expr_shift () ; 
 int /*<<< orphan*/  next () ; 
 scalar_t__ tok ; 

__attribute__((used)) static void expr_cmp(void) {
	expr_shift ();
	while ((tok >= TOK_ULE && tok <= TOK_GT) ||
	       tok == TOK_ULT || tok == TOK_UGE) {
		next ();
		expr_shift ();
	}
}