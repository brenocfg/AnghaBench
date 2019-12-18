#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ltree_gist ;
struct TYPE_4__ {int numlevel; } ;
typedef  TYPE_1__ ltree ;
typedef  void* int32 ;

/* Variables and functions */
 int /*<<< orphan*/  LTG_GETLNODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LTG_GETRNODE (int /*<<< orphan*/ *) ; 
 scalar_t__ ltree_compare (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
gist_isparent(ltree_gist *key, ltree *query)
{
	int32		numlevel = query->numlevel;
	int			i;

	for (i = query->numlevel; i >= 0; i--)
	{
		query->numlevel = i;
		if (ltree_compare(query, LTG_GETLNODE(key)) >= 0 && ltree_compare(query, LTG_GETRNODE(key)) <= 0)
		{
			query->numlevel = numlevel;
			return true;
		}
	}

	query->numlevel = numlevel;
	return false;
}