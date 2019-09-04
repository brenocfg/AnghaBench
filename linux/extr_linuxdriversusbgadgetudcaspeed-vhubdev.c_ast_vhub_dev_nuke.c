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
struct ast_vhub_dev {int /*<<< orphan*/ * epns; } ;

/* Variables and functions */
 unsigned int AST_VHUB_NUM_GEN_EPs ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  ast_vhub_nuke (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ast_vhub_dev_nuke(struct ast_vhub_dev *d)
{
	unsigned int i;

	for (i = 0; i < AST_VHUB_NUM_GEN_EPs; i++) {
		if (!d->epns[i])
			continue;
		ast_vhub_nuke(d->epns[i], -ESHUTDOWN);
	}
}