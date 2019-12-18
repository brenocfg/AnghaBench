#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_24__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_23__ {char* zToken; } ;
struct TYPE_28__ {scalar_t__ op; TYPE_1__ u; } ;
struct TYPE_27__ {int nArg; } ;
struct TYPE_26__ {TYPE_3__* pParse; } ;
struct TYPE_25__ {scalar_t__ nErr; TYPE_2__* db; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ NameContext ;
typedef  TYPE_5__ FuncDef ;
typedef  TYPE_6__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Expire ; 
 int /*<<< orphan*/  OP_Function0 ; 
 int /*<<< orphan*/  P4_FUNCDEF ; 
 int SQLITE_ATTACH ; 
 int SQLITE_OK ; 
 scalar_t__ TK_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int resolveAttachExpr (TYPE_4__*,TYPE_6__*) ; 
 int sqlite3AuthCheck (TYPE_3__*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_3__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_2__*,TYPE_6__*) ; 
 int sqlite3GetTempRange (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void codeAttach(
  Parse *pParse,       /* The parser context */
  int type,            /* Either SQLITE_ATTACH or SQLITE_DETACH */
  FuncDef const *pFunc,/* FuncDef wrapper for detachFunc() or attachFunc() */
  Expr *pAuthArg,      /* Expression to pass to authorization callback */
  Expr *pFilename,     /* Name of database file */
  Expr *pDbname,       /* Name of the database to use internally */
  Expr *pKey           /* Database key for encryption extension */
){
  int rc;
  NameContext sName;
  Vdbe *v;
  sqlite3* db = pParse->db;
  int regArgs;

  if( pParse->nErr ) goto attach_end;
  memset(&sName, 0, sizeof(NameContext));
  sName.pParse = pParse;

  if(
      SQLITE_OK!=(rc = resolveAttachExpr(&sName, pFilename)) ||
      SQLITE_OK!=(rc = resolveAttachExpr(&sName, pDbname)) ||
      SQLITE_OK!=(rc = resolveAttachExpr(&sName, pKey))
  ){
    goto attach_end;
  }

#ifndef SQLITE_OMIT_AUTHORIZATION
  if( pAuthArg ){
    char *zAuthArg;
    if( pAuthArg->op==TK_STRING ){
      zAuthArg = pAuthArg->u.zToken;
    }else{
      zAuthArg = 0;
    }
    rc = sqlite3AuthCheck(pParse, type, zAuthArg, 0, 0);
    if(rc!=SQLITE_OK ){
      goto attach_end;
    }
  }
#endif /* SQLITE_OMIT_AUTHORIZATION */


  v = sqlite3GetVdbe(pParse);
  regArgs = sqlite3GetTempRange(pParse, 4);
  sqlite3ExprCode(pParse, pFilename, regArgs);
  sqlite3ExprCode(pParse, pDbname, regArgs+1);
  sqlite3ExprCode(pParse, pKey, regArgs+2);

  assert( v || db->mallocFailed );
  if( v ){
    sqlite3VdbeAddOp4(v, OP_Function0, 0, regArgs+3-pFunc->nArg, regArgs+3,
                      (char *)pFunc, P4_FUNCDEF);
    assert( pFunc->nArg==-1 || (pFunc->nArg&0xff)==pFunc->nArg );
    sqlite3VdbeChangeP5(v, (u8)(pFunc->nArg));

    /* Code an OP_Expire. For an ATTACH statement, set P1 to true (expire this
    ** statement only). For DETACH, set it to false (expire all existing
    ** statements).
    */
    sqlite3VdbeAddOp1(v, OP_Expire, (type==SQLITE_ATTACH));
  }

attach_end:
  sqlite3ExprDelete(db, pFilename);
  sqlite3ExprDelete(db, pDbname);
  sqlite3ExprDelete(db, pKey);
}