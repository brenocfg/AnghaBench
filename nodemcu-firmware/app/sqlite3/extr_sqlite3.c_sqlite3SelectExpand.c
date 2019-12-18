#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  w ;
struct TYPE_6__ {int /*<<< orphan*/  xSelectCallback2; int /*<<< orphan*/  xSelectCallback; TYPE_2__* pParse; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_1__ Walker ;
struct TYPE_7__ {scalar_t__ hasCompound; } ;
typedef  int /*<<< orphan*/  Select ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  convertCompoundSelectToSubquery ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  selectExpander ; 
 int /*<<< orphan*/  selectPopWith ; 
 int /*<<< orphan*/  sqlite3ExprWalkNoop ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqlite3SelectExpand(Parse *pParse, Select *pSelect){
  Walker w;
  memset(&w, 0, sizeof(w));
  w.xExprCallback = sqlite3ExprWalkNoop;
  w.pParse = pParse;
  if( pParse->hasCompound ){
    w.xSelectCallback = convertCompoundSelectToSubquery;
    sqlite3WalkSelect(&w, pSelect);
  }
  w.xSelectCallback = selectExpander;
  w.xSelectCallback2 = selectPopWith;
  sqlite3WalkSelect(&w, pSelect);
}