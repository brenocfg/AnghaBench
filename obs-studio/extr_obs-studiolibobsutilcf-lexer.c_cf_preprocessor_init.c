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
struct cf_preprocessor {int ignore_state; int /*<<< orphan*/ * ed; int /*<<< orphan*/ * lex; int /*<<< orphan*/  tokens; int /*<<< orphan*/  dependencies; int /*<<< orphan*/  sys_include_dirs; int /*<<< orphan*/  defines; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 

void cf_preprocessor_init(struct cf_preprocessor *pp)
{
	da_init(pp->defines);
	da_init(pp->sys_include_dirs);
	da_init(pp->dependencies);
	da_init(pp->tokens);
	pp->lex = NULL;
	pp->ed = NULL;
	pp->ignore_state = false;
}