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
struct RowSetEntry {struct RowSetEntry* pRight; struct RowSetEntry* pLeft; } ;

/* Variables and functions */

__attribute__((used)) static struct RowSetEntry *rowSetNDeepTree(
  struct RowSetEntry **ppList,
  int iDepth
){
  struct RowSetEntry *p;         /* Root of the new tree */
  struct RowSetEntry *pLeft;     /* Left subtree */
  if( *ppList==0 ){ /*OPTIMIZATION-IF-TRUE*/
    /* Prevent unnecessary deep recursion when we run out of entries */
    return 0;
  }
  if( iDepth>1 ){   /*OPTIMIZATION-IF-TRUE*/
    /* This branch causes a *balanced* tree to be generated.  A valid tree
    ** is still generated without this branch, but the tree is wildly
    ** unbalanced and inefficient. */
    pLeft = rowSetNDeepTree(ppList, iDepth-1);
    p = *ppList;
    if( p==0 ){     /*OPTIMIZATION-IF-FALSE*/
      /* It is safe to always return here, but the resulting tree
      ** would be unbalanced */
      return pLeft;
    }
    p->pLeft = pLeft;
    *ppList = p->pRight;
    p->pRight = rowSetNDeepTree(ppList, iDepth-1);
  }else{
    p = *ppList;
    *ppList = p->pRight;
    p->pLeft = p->pRight = 0;
  }
  return p;
}