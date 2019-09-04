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
typedef  int /*<<< orphan*/  Table ;
struct TYPE_8__ {TYPE_1__* pFrom; struct TYPE_8__* pNextTo; } ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
struct TYPE_6__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ FKey ;

/* Variables and functions */
 TYPE_3__* sqlite3FkReferences (int /*<<< orphan*/ *) ; 
 char* whereOrName (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *whereForeignKeys(Parse *pParse, Table *pTab){
  FKey *p;
  char *zWhere = 0;
  for(p=sqlite3FkReferences(pTab); p; p=p->pNextTo){
    zWhere = whereOrName(pParse->db, zWhere, p->pFrom->zName);
  }
  return zWhere;
}