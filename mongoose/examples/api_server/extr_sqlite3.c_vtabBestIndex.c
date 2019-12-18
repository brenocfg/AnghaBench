#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ zErrMsg; TYPE_1__* pModule; } ;
typedef  TYPE_4__ sqlite3_vtab ;
struct TYPE_25__ {int nConstraint; TYPE_3__* aConstraintUsage; TYPE_2__* aConstraint; } ;
typedef  TYPE_5__ sqlite3_index_info ;
struct TYPE_26__ {scalar_t__ zName; } ;
typedef  TYPE_6__ Table ;
struct TYPE_27__ {int nErr; TYPE_14__* db; } ;
struct TYPE_23__ {scalar_t__ argvIndex; } ;
struct TYPE_22__ {int /*<<< orphan*/  usable; } ;
struct TYPE_21__ {int (* xBestIndex ) (TYPE_4__*,TYPE_5__*) ;} ;
struct TYPE_20__ {int mallocFailed; } ;
struct TYPE_19__ {TYPE_4__* pVtab; } ;
typedef  TYPE_7__ Parse ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE_IDX_INPUTS (TYPE_5__*) ; 
 int /*<<< orphan*/  TRACE_IDX_OUTPUTS (TYPE_5__*) ; 
 int /*<<< orphan*/  WHERETRACE (char*) ; 
 scalar_t__ sqlite3ErrStr (int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_7__*,char*,scalar_t__) ; 
 TYPE_13__* sqlite3GetVTable (TYPE_14__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 int stub1 (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static int vtabBestIndex(Parse *pParse, Table *pTab, sqlite3_index_info *p){
  sqlite3_vtab *pVtab = sqlite3GetVTable(pParse->db, pTab)->pVtab;
  int i;
  int rc;

  WHERETRACE(("xBestIndex for %s\n", pTab->zName));
  TRACE_IDX_INPUTS(p);
  rc = pVtab->pModule->xBestIndex(pVtab, p);
  TRACE_IDX_OUTPUTS(p);

  if( rc!=SQLITE_OK ){
    if( rc==SQLITE_NOMEM ){
      pParse->db->mallocFailed = 1;
    }else if( !pVtab->zErrMsg ){
      sqlite3ErrorMsg(pParse, "%s", sqlite3ErrStr(rc));
    }else{
      sqlite3ErrorMsg(pParse, "%s", pVtab->zErrMsg);
    }
  }
  sqlite3_free(pVtab->zErrMsg);
  pVtab->zErrMsg = 0;

  for(i=0; i<p->nConstraint; i++){
    if( !p->aConstraint[i].usable && p->aConstraintUsage[i].argvIndex>0 ){
      sqlite3ErrorMsg(pParse, 
          "table %s: xBestIndex returned an invalid plan", pTab->zName);
    }
  }

  return pParse->nErr;
}