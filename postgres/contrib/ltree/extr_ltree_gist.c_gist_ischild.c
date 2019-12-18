#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ltree_gist ;
struct TYPE_7__ {scalar_t__ numlevel; } ;
typedef  TYPE_1__ ltree ;

/* Variables and functions */
 int /*<<< orphan*/  LTG_GETLNODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LTG_GETRNODE (int /*<<< orphan*/ *) ; 
 TYPE_1__* copy_ltree (int /*<<< orphan*/ ) ; 
 scalar_t__ ltree_compare (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static bool
gist_ischild(ltree_gist *key, ltree *query)
{
	ltree	   *left = copy_ltree(LTG_GETLNODE(key));
	ltree	   *right = copy_ltree(LTG_GETRNODE(key));
	bool		res = true;

	if (left->numlevel > query->numlevel)
		left->numlevel = query->numlevel;

	if (ltree_compare(query, left) < 0)
		res = false;

	if (right->numlevel > query->numlevel)
		right->numlevel = query->numlevel;

	if (res && ltree_compare(query, right) > 0)
		res = false;

	pfree(left);
	pfree(right);

	return res;
}