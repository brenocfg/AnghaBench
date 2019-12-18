#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int wtFlags; int prereqAll; size_t iParent; scalar_t__ nChild; TYPE_1__* pWC; int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_2__ WhereTerm ;
struct TYPE_8__ {scalar_t__ iLeftJoin; int notReady; } ;
typedef  TYPE_3__ WhereLevel ;
struct TYPE_6__ {TYPE_2__* a; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 scalar_t__ ExprHasProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TERM_CODED ; 
 int TERM_LIKE ; 
 int TERM_LIKECOND ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void disableTerm(WhereLevel *pLevel, WhereTerm *pTerm){
  int nLoop = 0;
  assert( pTerm!=0 );
  while( (pTerm->wtFlags & TERM_CODED)==0
      && (pLevel->iLeftJoin==0 || ExprHasProperty(pTerm->pExpr, EP_FromJoin))
      && (pLevel->notReady & pTerm->prereqAll)==0
  ){
    if( nLoop && (pTerm->wtFlags & TERM_LIKE)!=0 ){
      pTerm->wtFlags |= TERM_LIKECOND;
    }else{
      pTerm->wtFlags |= TERM_CODED;
    }
    if( pTerm->iParent<0 ) break;
    pTerm = &pTerm->pWC->a[pTerm->iParent];
    assert( pTerm!=0 );
    pTerm->nChild--;
    if( pTerm->nChild!=0 ) break;
    nLoop++;
  }
}