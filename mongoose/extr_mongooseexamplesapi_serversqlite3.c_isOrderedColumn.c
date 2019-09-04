#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {TYPE_5__* pIdx; } ;
struct TYPE_8__ {int wsFlags; TYPE_1__ u; } ;
struct TYPE_9__ {int iTabCur; TYPE_2__ plan; } ;
typedef  TYPE_3__ WhereLevel ;
struct TYPE_10__ {int i; TYPE_3__* aLevel; } ;
typedef  TYPE_4__ WhereBestIdx ;
struct TYPE_11__ {int nColumn; int* aiColumn; int* aSortOrder; } ;
typedef  TYPE_5__ Index ;

/* Variables and functions */
 int WHERE_ALL_UNIQUE ; 
 int WHERE_ORDERED ; 
 int WHERE_REVERSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int isOrderedColumn(
  WhereBestIdx *p,
  int iTab,
  int iCol
){
  int i, j;
  WhereLevel *pLevel = &p->aLevel[p->i-1];
  Index *pIdx;
  u8 sortOrder;
  for(i=p->i-1; i>=0; i--, pLevel--){
    if( pLevel->iTabCur!=iTab ) continue;
    if( (pLevel->plan.wsFlags & WHERE_ALL_UNIQUE)!=0 ){
      return 1;
    }
    assert( (pLevel->plan.wsFlags & WHERE_ORDERED)!=0 );
    if( (pIdx = pLevel->plan.u.pIdx)!=0 ){
      if( iCol<0 ){
        sortOrder = 0;
        testcase( (pLevel->plan.wsFlags & WHERE_REVERSE)!=0 );
      }else{
        int n = pIdx->nColumn;
        for(j=0; j<n; j++){
          if( iCol==pIdx->aiColumn[j] ) break;
        }
        if( j>=n ) return 0;
        sortOrder = pIdx->aSortOrder[j];
        testcase( (pLevel->plan.wsFlags & WHERE_REVERSE)!=0 );
      }
    }else{
      if( iCol!=(-1) ) return 0;
      sortOrder = 0;
      testcase( (pLevel->plan.wsFlags & WHERE_REVERSE)!=0 );
    }
    if( (pLevel->plan.wsFlags & WHERE_REVERSE)!=0 ){
      assert( sortOrder==0 || sortOrder==1 );
      testcase( sortOrder==1 );
      sortOrder = 1 - sortOrder;
    }
    return sortOrder+2;
  }
  return 0;
}