#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tabFlags; int /*<<< orphan*/  zName; } ;
typedef  TYPE_2__ Table ;
struct TYPE_9__ {TYPE_1__* db; } ;
struct TYPE_7__ {int flags; scalar_t__ nVdbeExec; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int SQLITE_Defensive ; 
 int TF_Shadow ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3StrNICmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int isAlterableTable(Parse *pParse, Table *pTab){
  if( 0==sqlite3StrNICmp(pTab->zName, "sqlite_", 7) 
#ifndef SQLITE_OMIT_VIRTUALTABLE
   || ( (pTab->tabFlags & TF_Shadow) 
     && (pParse->db->flags & SQLITE_Defensive)
     && pParse->db->nVdbeExec==0
   )
#endif
  ){
    sqlite3ErrorMsg(pParse, "table %s may not be altered", pTab->zName);
    return 1;
  }
  return 0;
}