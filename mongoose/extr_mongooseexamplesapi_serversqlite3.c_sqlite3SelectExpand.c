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
typedef  int /*<<< orphan*/  w ;
struct TYPE_4__ {int /*<<< orphan*/  xSelectCallback; int /*<<< orphan*/ * pParse; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_1__ Walker ;
typedef  int /*<<< orphan*/  Select ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  convertCompoundSelectToSubquery ; 
 int /*<<< orphan*/  exprWalkNoop ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  selectExpander ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqlite3SelectExpand(Parse *pParse, Select *pSelect){
  Walker w;
  memset(&w, 0, sizeof(w));
  w.xSelectCallback = convertCompoundSelectToSubquery;
  w.xExprCallback = exprWalkNoop;
  w.pParse = pParse;
  sqlite3WalkSelect(&w, pSelect);
  w.xSelectCallback = selectExpander;
  sqlite3WalkSelect(&w, pSelect);
}