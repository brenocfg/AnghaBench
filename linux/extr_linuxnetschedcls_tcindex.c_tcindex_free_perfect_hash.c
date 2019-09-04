#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcindex_data {int hash; TYPE_1__* perfect; } ;
struct TYPE_2__ {int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  tcf_exts_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcindex_free_perfect_hash(struct tcindex_data *cp)
{
	int i;

	for (i = 0; i < cp->hash; i++)
		tcf_exts_destroy(&cp->perfect[i].exts);
	kfree(cp->perfect);
}