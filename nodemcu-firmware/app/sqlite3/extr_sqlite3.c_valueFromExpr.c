#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ValueNewStat4Ctx {int dummy; } ;
struct TYPE_22__ {double r; scalar_t__ i; } ;
struct TYPE_24__ {int flags; TYPE_1__ u; } ;
typedef  TYPE_3__ sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int i64 ;
struct TYPE_23__ {char* zToken; scalar_t__ iValue; } ;
struct TYPE_25__ {int op; int op2; int flags; TYPE_2__ u; struct TYPE_25__* pLeft; } ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_IntValue ; 
 int EP_TokenOnly ; 
 scalar_t__ ExprHasProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int MEM_Int ; 
 int MEM_Real ; 
 int MEM_Str ; 
 int /*<<< orphan*/  MemSetTypeFlag (TYPE_3__*,int) ; 
 scalar_t__ NEVER (int) ; 
 scalar_t__ SMALLEST_INT64 ; 
 int /*<<< orphan*/  SQLITE_AFF_BLOB ; 
 int /*<<< orphan*/  SQLITE_AFF_NUMERIC ; 
 int /*<<< orphan*/  SQLITE_DYNAMIC ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int TK_BLOB ; 
 int TK_CAST ; 
 int TK_FLOAT ; 
 int TK_FUNCTION ; 
 int TK_INTEGER ; 
 int TK_NULL ; 
 int TK_REGISTER ; 
 int TK_SPAN ; 
 int TK_STRING ; 
 int TK_UMINUS ; 
 int TK_UPLUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3AffinityType (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3HexToBlob (int /*<<< orphan*/ *,char*,int) ; 
 char* sqlite3MPrintf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 int /*<<< orphan*/  sqlite3OomFault (int /*<<< orphan*/ *) ; 
 int sqlite3Strlen30 (char*) ; 
 int /*<<< orphan*/  sqlite3ValueApplyAffinity (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ValueFree (TYPE_3__*) ; 
 int sqlite3ValueFromExpr (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  sqlite3ValueSetStr (TYPE_3__*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeChangeEncoding (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemCast (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemNumerify (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetInt64 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetStr (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int valueFromFunction (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**,struct ValueNewStat4Ctx*) ; 
 TYPE_3__* valueNew (int /*<<< orphan*/ *,struct ValueNewStat4Ctx*) ; 

__attribute__((used)) static int valueFromExpr(
  sqlite3 *db,                    /* The database connection */
  Expr *pExpr,                    /* The expression to evaluate */
  u8 enc,                         /* Encoding to use */
  u8 affinity,                    /* Affinity to use */
  sqlite3_value **ppVal,          /* Write the new value here */
  struct ValueNewStat4Ctx *pCtx   /* Second argument for valueNew() */
){
  int op;
  char *zVal = 0;
  sqlite3_value *pVal = 0;
  int negInt = 1;
  const char *zNeg = "";
  int rc = SQLITE_OK;

  assert( pExpr!=0 );
  while( (op = pExpr->op)==TK_UPLUS || op==TK_SPAN ) pExpr = pExpr->pLeft;
  if( NEVER(op==TK_REGISTER) ) op = pExpr->op2;

  /* Compressed expressions only appear when parsing the DEFAULT clause
  ** on a table column definition, and hence only when pCtx==0.  This
  ** check ensures that an EP_TokenOnly expression is never passed down
  ** into valueFromFunction(). */
  assert( (pExpr->flags & EP_TokenOnly)==0 || pCtx==0 );

  if( op==TK_CAST ){
    u8 aff = sqlite3AffinityType(pExpr->u.zToken,0);
    rc = valueFromExpr(db, pExpr->pLeft, enc, aff, ppVal, pCtx);
    testcase( rc!=SQLITE_OK );
    if( *ppVal ){
      sqlite3VdbeMemCast(*ppVal, aff, SQLITE_UTF8);
      sqlite3ValueApplyAffinity(*ppVal, affinity, SQLITE_UTF8);
    }
    return rc;
  }

  /* Handle negative integers in a single step.  This is needed in the
  ** case when the value is -9223372036854775808.
  */
  if( op==TK_UMINUS
   && (pExpr->pLeft->op==TK_INTEGER || pExpr->pLeft->op==TK_FLOAT) ){
    pExpr = pExpr->pLeft;
    op = pExpr->op;
    negInt = -1;
    zNeg = "-";
  }

  if( op==TK_STRING || op==TK_FLOAT || op==TK_INTEGER ){
    pVal = valueNew(db, pCtx);
    if( pVal==0 ) goto no_mem;
    if( ExprHasProperty(pExpr, EP_IntValue) ){
      sqlite3VdbeMemSetInt64(pVal, (i64)pExpr->u.iValue*negInt);
    }else{
      zVal = sqlite3MPrintf(db, "%s%s", zNeg, pExpr->u.zToken);
      if( zVal==0 ) goto no_mem;
      sqlite3ValueSetStr(pVal, -1, zVal, SQLITE_UTF8, SQLITE_DYNAMIC);
    }
    if( (op==TK_INTEGER || op==TK_FLOAT ) && affinity==SQLITE_AFF_BLOB ){
      sqlite3ValueApplyAffinity(pVal, SQLITE_AFF_NUMERIC, SQLITE_UTF8);
    }else{
      sqlite3ValueApplyAffinity(pVal, affinity, SQLITE_UTF8);
    }
    if( pVal->flags & (MEM_Int|MEM_Real) ) pVal->flags &= ~MEM_Str;
    if( enc!=SQLITE_UTF8 ){
      rc = sqlite3VdbeChangeEncoding(pVal, enc);
    }
  }else if( op==TK_UMINUS ) {
    /* This branch happens for multiple negative signs.  Ex: -(-5) */
    if( SQLITE_OK==sqlite3ValueFromExpr(db,pExpr->pLeft,enc,affinity,&pVal)
     && pVal!=0
    ){
      sqlite3VdbeMemNumerify(pVal);
      if( pVal->flags & MEM_Real ){
        pVal->u.r = -pVal->u.r;
      }else if( pVal->u.i==SMALLEST_INT64 ){
        pVal->u.r = -(double)SMALLEST_INT64;
        MemSetTypeFlag(pVal, MEM_Real);
      }else{
        pVal->u.i = -pVal->u.i;
      }
      sqlite3ValueApplyAffinity(pVal, affinity, enc);
    }
  }else if( op==TK_NULL ){
    pVal = valueNew(db, pCtx);
    if( pVal==0 ) goto no_mem;
    sqlite3VdbeMemNumerify(pVal);
  }
#ifndef SQLITE_OMIT_BLOB_LITERAL
  else if( op==TK_BLOB ){
    int nVal;
    assert( pExpr->u.zToken[0]=='x' || pExpr->u.zToken[0]=='X' );
    assert( pExpr->u.zToken[1]=='\'' );
    pVal = valueNew(db, pCtx);
    if( !pVal ) goto no_mem;
    zVal = &pExpr->u.zToken[2];
    nVal = sqlite3Strlen30(zVal)-1;
    assert( zVal[nVal]=='\'' );
    sqlite3VdbeMemSetStr(pVal, sqlite3HexToBlob(db, zVal, nVal), nVal/2,
                         0, SQLITE_DYNAMIC);
  }
#endif

#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  else if( op==TK_FUNCTION && pCtx!=0 ){
    rc = valueFromFunction(db, pExpr, enc, affinity, &pVal, pCtx);
  }
#endif

  *ppVal = pVal;
  return rc;

no_mem:
  sqlite3OomFault(db);
  sqlite3DbFree(db, zVal);
  assert( *ppVal==0 );
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  if( pCtx==0 ) sqlite3ValueFree(pVal);
#else
  assert( pCtx==0 ); sqlite3ValueFree(pVal);
#endif
  return SQLITE_NOMEM_BKPT;
}