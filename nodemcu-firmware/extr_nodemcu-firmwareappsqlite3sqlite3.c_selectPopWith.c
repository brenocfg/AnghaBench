#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* pOuter; } ;
typedef  TYPE_1__ With ;
struct TYPE_10__ {TYPE_4__* pParse; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_13__ {TYPE_1__* pWith; } ;
struct TYPE_12__ {TYPE_1__* pWith; } ;
struct TYPE_11__ {scalar_t__ pPrior; } ;
typedef  TYPE_3__ Select ;
typedef  TYPE_4__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* findRightmost (TYPE_3__*) ; 

__attribute__((used)) static void selectPopWith(Walker *pWalker, Select *p){
  Parse *pParse = pWalker->pParse;
  if( pParse->pWith && p->pPrior==0 ){
    With *pWith = findRightmost(p)->pWith;
    if( pWith!=0 ){
      assert( pParse->pWith==pWith );
      pParse->pWith = pWith->pOuter;
    }
  }
}