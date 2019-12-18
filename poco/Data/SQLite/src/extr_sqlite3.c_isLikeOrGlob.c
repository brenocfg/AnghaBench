#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_29__ {int flags; } ;
typedef  TYPE_5__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_28__ {char* zToken; } ;
struct TYPE_27__ {int /*<<< orphan*/  pTab; } ;
struct TYPE_25__ {TYPE_7__* pList; } ;
struct TYPE_32__ {int op; int iColumn; TYPE_4__ u; TYPE_3__ y; TYPE_1__ x; } ;
struct TYPE_31__ {TYPE_2__* a; } ;
struct TYPE_30__ {int /*<<< orphan*/ * pVdbe; int /*<<< orphan*/ * pReprepare; TYPE_5__* db; } ;
struct TYPE_26__ {TYPE_8__* pExpr; } ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ ExprList ;
typedef  TYPE_8__ Expr ;

/* Variables and functions */
 scalar_t__ IsVirtual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_AFF_BLOB ; 
 scalar_t__ SQLITE_AFF_TEXT ; 
 int SQLITE_EnableQPSG ; 
 scalar_t__ SQLITE_TEXT ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 scalar_t__ TK_COLUMN ; 
 int TK_REGISTER ; 
 int TK_STRING ; 
 int TK_VARIABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3AtoF (char*,double*,int,int /*<<< orphan*/ ) ; 
 TYPE_8__* sqlite3Expr (TYPE_5__*,int,char*) ; 
 scalar_t__ sqlite3ExprAffinity (TYPE_8__*) ; 
 int /*<<< orphan*/  sqlite3ExprCodeTarget (TYPE_6__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_5__*,TYPE_8__*) ; 
 TYPE_8__* sqlite3ExprSkipCollate (TYPE_8__*) ; 
 int sqlite3GetTempReg (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3IsLikeFunction (TYPE_5__*,TYPE_8__*,int*,char*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_6__*,int) ; 
 int /*<<< orphan*/  sqlite3ValueFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP3 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3VdbeGetBoundValue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeSetVarmask (int /*<<< orphan*/ *,int) ; 
 scalar_t__* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isLikeOrGlob(
  Parse *pParse,    /* Parsing and code generating context */
  Expr *pExpr,      /* Test this expression */
  Expr **ppPrefix,  /* Pointer to TK_STRING expression with pattern prefix */
  int *pisComplete, /* True if the only wildcard is % in the last character */
  int *pnoCase      /* True if uppercase is equivalent to lowercase */
){
  const u8 *z = 0;           /* String on RHS of LIKE operator */
  Expr *pRight, *pLeft;      /* Right and left size of LIKE operator */
  ExprList *pList;           /* List of operands to the LIKE operator */
  u8 c;                      /* One character in z[] */
  int cnt;                   /* Number of non-wildcard prefix characters */
  u8 wc[4];                  /* Wildcard characters */
  sqlite3 *db = pParse->db;  /* Database connection */
  sqlite3_value *pVal = 0;
  int op;                    /* Opcode of pRight */
  int rc;                    /* Result code to return */

  if( !sqlite3IsLikeFunction(db, pExpr, pnoCase, (char*)wc) ){
    return 0;
  }
#ifdef SQLITE_EBCDIC
  if( *pnoCase ) return 0;
#endif
  pList = pExpr->x.pList;
  pLeft = pList->a[1].pExpr;

  pRight = sqlite3ExprSkipCollate(pList->a[0].pExpr);
  op = pRight->op;
  if( op==TK_VARIABLE && (db->flags & SQLITE_EnableQPSG)==0 ){
    Vdbe *pReprepare = pParse->pReprepare;
    int iCol = pRight->iColumn;
    pVal = sqlite3VdbeGetBoundValue(pReprepare, iCol, SQLITE_AFF_BLOB);
    if( pVal && sqlite3_value_type(pVal)==SQLITE_TEXT ){
      z = sqlite3_value_text(pVal);
    }
    sqlite3VdbeSetVarmask(pParse->pVdbe, iCol);
    assert( pRight->op==TK_VARIABLE || pRight->op==TK_REGISTER );
  }else if( op==TK_STRING ){
    z = (u8*)pRight->u.zToken;
  }
  if( z ){

    /* Count the number of prefix characters prior to the first wildcard */
    cnt = 0;
    while( (c=z[cnt])!=0 && c!=wc[0] && c!=wc[1] && c!=wc[2] ){
      cnt++;
      if( c==wc[3] && z[cnt]!=0 ) cnt++;
    }

    /* The optimization is possible only if (1) the pattern does not begin
    ** with a wildcard and if (2) the non-wildcard prefix does not end with
    ** an (illegal 0xff) character, or (3) the pattern does not consist of
    ** a single escape character. The second condition is necessary so
    ** that we can increment the prefix key to find an upper bound for the
    ** range search. The third is because the caller assumes that the pattern
    ** consists of at least one character after all escapes have been
    ** removed.  */
    if( cnt!=0 && 255!=(u8)z[cnt-1] && (cnt>1 || z[0]!=wc[3]) ){
      Expr *pPrefix;

      /* A "complete" match if the pattern ends with "*" or "%" */
      *pisComplete = c==wc[0] && z[cnt+1]==0;

      /* Get the pattern prefix.  Remove all escapes from the prefix. */
      pPrefix = sqlite3Expr(db, TK_STRING, (char*)z);
      if( pPrefix ){
        int iFrom, iTo;
        char *zNew = pPrefix->u.zToken;
        zNew[cnt] = 0;
        for(iFrom=iTo=0; iFrom<cnt; iFrom++){
          if( zNew[iFrom]==wc[3] ) iFrom++;
          zNew[iTo++] = zNew[iFrom];
        }
        zNew[iTo] = 0;
        assert( iTo>0 );

        /* If the LHS is not an ordinary column with TEXT affinity, then the
        ** pattern prefix boundaries (both the start and end boundaries) must
        ** not look like a number.  Otherwise the pattern might be treated as
        ** a number, which will invalidate the LIKE optimization.
        **
        ** Getting this right has been a persistent source of bugs in the
        ** LIKE optimization.  See, for example:
        **    2018-09-10 https://sqlite.org/src/info/c94369cae9b561b1
        **    2019-05-02 https://sqlite.org/src/info/b043a54c3de54b28
        **    2019-06-10 https://sqlite.org/src/info/fd76310a5e843e07
        **    2019-06-14 https://sqlite.org/src/info/ce8717f0885af975
        */
        if( pLeft->op!=TK_COLUMN 
         || sqlite3ExprAffinity(pLeft)!=SQLITE_AFF_TEXT 
         || IsVirtual(pLeft->y.pTab)  /* Value might be numeric */
        ){
          int isNum;
          double rDummy;
          isNum = sqlite3AtoF(zNew, &rDummy, iTo, SQLITE_UTF8);
          if( isNum<=0 ){
            zNew[iTo-1]++;
            isNum = sqlite3AtoF(zNew, &rDummy, iTo, SQLITE_UTF8);
            zNew[iTo-1]--;
          }
          if( isNum>0 ){
            sqlite3ExprDelete(db, pPrefix);
            sqlite3ValueFree(pVal);
            return 0;
          }
        }
      }
      *ppPrefix = pPrefix;

      /* If the RHS pattern is a bound parameter, make arrangements to
      ** reprepare the statement when that parameter is rebound */
      if( op==TK_VARIABLE ){
        Vdbe *v = pParse->pVdbe;
        sqlite3VdbeSetVarmask(v, pRight->iColumn);
        if( *pisComplete && pRight->u.zToken[1] ){
          /* If the rhs of the LIKE expression is a variable, and the current
          ** value of the variable means there is no need to invoke the LIKE
          ** function, then no OP_Variable will be added to the program.
          ** This causes problems for the sqlite3_bind_parameter_name()
          ** API. To work around them, add a dummy OP_Variable here.
          */ 
          int r1 = sqlite3GetTempReg(pParse);
          sqlite3ExprCodeTarget(pParse, pRight, r1);
          sqlite3VdbeChangeP3(v, sqlite3VdbeCurrentAddr(v)-1, 0);
          sqlite3ReleaseTempReg(pParse, r1);
        }
      }
    }else{
      z = 0;
    }
  }

  rc = (z!=0);
  sqlite3ValueFree(pVal);
  return rc;
}