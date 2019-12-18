#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ xSelectCallback2; int /*<<< orphan*/  xSelectCallback; TYPE_2__* pParse; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_1__ Walker ;
struct TYPE_6__ {int /*<<< orphan*/  hasCompound; } ;
typedef  int /*<<< orphan*/  Select ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 scalar_t__ OK_IF_ALWAYS_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convertCompoundSelectToSubquery ; 
 int /*<<< orphan*/  selectExpander ; 
 scalar_t__ selectPopWith ; 
 int /*<<< orphan*/  sqlite3ExprWalkNoop ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqlite3SelectExpand(Parse *pParse, Select *pSelect){
  Walker w;
  w.xExprCallback = sqlite3ExprWalkNoop;
  w.pParse = pParse;
  if( OK_IF_ALWAYS_TRUE(pParse->hasCompound) ){
    w.xSelectCallback = convertCompoundSelectToSubquery;
    w.xSelectCallback2 = 0;
    sqlite3WalkSelect(&w, pSelect);
  }
  w.xSelectCallback = selectExpander;
  w.xSelectCallback2 = selectPopWith;
  sqlite3WalkSelect(&w, pSelect);
}