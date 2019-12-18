#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ numlevel; } ;
typedef  TYPE_1__ ltree ;

/* Variables and functions */
 char* LTREE_FIRST (TYPE_1__*) ; 
 int LTREE_HDRSIZE ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int) ; 
 int VARSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static ltree *
ltree_concat(ltree *a, ltree *b)
{
	ltree	   *r;

	r = (ltree *) palloc0(VARSIZE(a) + VARSIZE(b) - LTREE_HDRSIZE);
	SET_VARSIZE(r, VARSIZE(a) + VARSIZE(b) - LTREE_HDRSIZE);
	r->numlevel = a->numlevel + b->numlevel;

	memcpy(LTREE_FIRST(r), LTREE_FIRST(a), VARSIZE(a) - LTREE_HDRSIZE);
	memcpy(((char *) LTREE_FIRST(r)) + VARSIZE(a) - LTREE_HDRSIZE,
		   LTREE_FIRST(b),
		   VARSIZE(b) - LTREE_HDRSIZE);
	return r;
}