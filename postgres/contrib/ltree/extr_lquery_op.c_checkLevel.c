#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ len; char const* name; } ;
typedef  TYPE_1__ ltree_level ;
struct TYPE_12__ {int flag; char const* name; scalar_t__ len; } ;
typedef  TYPE_2__ lquery_variant ;
struct TYPE_13__ {int numvar; } ;
typedef  TYPE_3__ lquery_level ;

/* Variables and functions */
 TYPE_2__* LQL_FIRST (TYPE_3__*) ; 
 int LVAR_ANYEND ; 
 int LVAR_INCASE ; 
 TYPE_2__* LVAR_NEXT (TYPE_2__*) ; 
 int LVAR_SUBLEXEME ; 
 scalar_t__ compare_subnode (TYPE_1__*,char const*,scalar_t__,int (*) (char const*,char const*,size_t),int) ; 
 int ltree_strncasecmp (char const*,char const*,size_t) ; 
 int strncmp (char const*,char const*,size_t) ; 
 int stub1 (char const*,char const*,size_t) ; 

__attribute__((used)) static bool
checkLevel(lquery_level *curq, ltree_level *curt)
{
	int			(*cmpptr) (const char *, const char *, size_t);
	lquery_variant *curvar = LQL_FIRST(curq);
	int			i;

	for (i = 0; i < curq->numvar; i++)
	{
		cmpptr = (curvar->flag & LVAR_INCASE) ? ltree_strncasecmp : strncmp;

		if (curvar->flag & LVAR_SUBLEXEME)
		{
			if (compare_subnode(curt, curvar->name, curvar->len, cmpptr, (curvar->flag & LVAR_ANYEND)))
				return true;
		}
		else if (
				 (
				  curvar->len == curt->len ||
				  (curt->len > curvar->len && (curvar->flag & LVAR_ANYEND))
				  ) &&
				 (*cmpptr) (curvar->name, curt->name, curvar->len) == 0)
		{

			return true;
		}
		curvar = LVAR_NEXT(curvar);
	}
	return false;
}