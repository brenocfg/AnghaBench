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
 int /*<<< orphan*/  assert (int) ; 
 struct RowSetEntry* rowSetNDeepTree (struct RowSetEntry**,int) ; 

__attribute__((used)) static struct RowSetEntry *rowSetListToTree(struct RowSetEntry *pList){
  int iDepth;           /* Depth of the tree so far */
  struct RowSetEntry *p;       /* Current tree root */
  struct RowSetEntry *pLeft;   /* Left subtree */

  assert( pList!=0 );
  p = pList;
  pList = p->pRight;
  p->pLeft = p->pRight = 0;
  for(iDepth=1; pList; iDepth++){
    pLeft = p;
    p = pList;
    pList = p->pRight;
    p->pLeft = pLeft;
    p->pRight = rowSetNDeepTree(&pList, iDepth);
  }
  return p;
}