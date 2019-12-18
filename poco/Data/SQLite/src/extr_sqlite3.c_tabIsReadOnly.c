#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int flags; scalar_t__ pVtabCtx; scalar_t__ nVdbeExec; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_16__ {int tabFlags; } ;
typedef  TYPE_4__ Table ;
struct TYPE_18__ {TYPE_2__* pMod; } ;
struct TYPE_17__ {scalar_t__ nested; TYPE_3__* db; } ;
struct TYPE_14__ {TYPE_1__* pModule; } ;
struct TYPE_13__ {scalar_t__ xUpdate; } ;
typedef  TYPE_5__ Parse ;

/* Variables and functions */
 scalar_t__ IsVirtual (TYPE_4__*) ; 
 int SQLITE_Defensive ; 
 int TF_Readonly ; 
 int TF_Shadow ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_9__* sqlite3GetVTable (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ sqlite3WritableSchema (TYPE_3__*) ; 

__attribute__((used)) static int tabIsReadOnly(Parse *pParse, Table *pTab){
  sqlite3 *db;
  if( IsVirtual(pTab) ){
    return sqlite3GetVTable(pParse->db, pTab)->pMod->pModule->xUpdate==0;
  }
  if( (pTab->tabFlags & (TF_Readonly|TF_Shadow))==0 ) return 0;
  db = pParse->db;
  if( (pTab->tabFlags & TF_Readonly)!=0 ){
    return sqlite3WritableSchema(db)==0 && pParse->nested==0;
  }
  assert( pTab->tabFlags & TF_Shadow );
  return (db->flags & SQLITE_Defensive)!=0 
#ifndef SQLITE_OMIT_VIRTUALTABLE
          && db->pVtabCtx==0
#endif
          && db->nVdbeExec==0;
}