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
struct expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_AND ; 
 struct expr* expr_alloc_two (int /*<<< orphan*/ ,struct expr*,struct expr*) ; 

struct expr *expr_alloc_and(struct expr *e1, struct expr *e2)
{
	if (!e1)
		return e2;
	return e2 ? expr_alloc_two(E_AND, e1, e2) : e1;
}