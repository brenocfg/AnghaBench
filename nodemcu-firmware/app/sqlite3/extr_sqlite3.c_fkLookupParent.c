#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_23__ {int iPKey; } ;
typedef  TYPE_1__ Table ;
struct TYPE_26__ {int isDeferred; int nCol; TYPE_1__* pFrom; } ;
struct TYPE_25__ {int tnum; int* aiColumn; } ;
struct TYPE_24__ {int nTab; int /*<<< orphan*/  isMultiWrite; int /*<<< orphan*/  pToplevel; TYPE_12__* db; } ;
struct TYPE_22__ {int flags; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Index ;
typedef  TYPE_4__ FKey ;

/* Variables and functions */
 int /*<<< orphan*/  OE_Abort ; 
 int /*<<< orphan*/  OP_Close ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_Eq ; 
 int /*<<< orphan*/  OP_FkCounter ; 
 int /*<<< orphan*/  OP_FkIfZero ; 
 int /*<<< orphan*/  OP_Found ; 
 int /*<<< orphan*/  OP_IsNull ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_MustBeInt ; 
 int /*<<< orphan*/  OP_Ne ; 
 int /*<<< orphan*/  OP_NotExists ; 
 int /*<<< orphan*/  OP_OpenRead ; 
 int /*<<< orphan*/  OP_SCopy ; 
 int /*<<< orphan*/  P4_STATIC ; 
 int /*<<< orphan*/  P5_ConstraintFK ; 
 int /*<<< orphan*/  SQLITE_CONSTRAINT_FOREIGNKEY ; 
 int SQLITE_DeferFKs ; 
 int /*<<< orphan*/  SQLITE_JUMPIFNULL ; 
 int /*<<< orphan*/  SQLITE_NOTNULL ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3GetTempRange (TYPE_2__*,int) ; 
 int sqlite3GetTempReg (TYPE_2__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3HaltConstraint (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IndexAffinityStr (TYPE_12__*,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3MayAbort (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3OpenTable (TYPE_2__*,int,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempRange (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeSetP4KeyInfo (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void fkLookupParent(
  Parse *pParse,        /* Parse context */
  int iDb,              /* Index of database housing pTab */
  Table *pTab,          /* Parent table of FK pFKey */
  Index *pIdx,          /* Unique index on parent key columns in pTab */
  FKey *pFKey,          /* Foreign key constraint */
  int *aiCol,           /* Map from parent key columns to child table columns */
  int regData,          /* Address of array containing child table row */
  int nIncr,            /* Increment constraint counter by this */
  int isIgnore          /* If true, pretend pTab contains all NULL values */
){
  int i;                                    /* Iterator variable */
  Vdbe *v = sqlite3GetVdbe(pParse);         /* Vdbe to add code to */
  int iCur = pParse->nTab - 1;              /* Cursor number to use */
  int iOk = sqlite3VdbeMakeLabel(v);        /* jump here if parent key found */

  /* If nIncr is less than zero, then check at runtime if there are any
  ** outstanding constraints to resolve. If there are not, there is no need
  ** to check if deleting this row resolves any outstanding violations.
  **
  ** Check if any of the key columns in the child table row are NULL. If
  ** any are, then the constraint is considered satisfied. No need to
  ** search for a matching row in the parent table.  */
  if( nIncr<0 ){
    sqlite3VdbeAddOp2(v, OP_FkIfZero, pFKey->isDeferred, iOk);
    VdbeCoverage(v);
  }
  for(i=0; i<pFKey->nCol; i++){
    int iReg = aiCol[i] + regData + 1;
    sqlite3VdbeAddOp2(v, OP_IsNull, iReg, iOk); VdbeCoverage(v);
  }

  if( isIgnore==0 ){
    if( pIdx==0 ){
      /* If pIdx is NULL, then the parent key is the INTEGER PRIMARY KEY
      ** column of the parent table (table pTab).  */
      int iMustBeInt;               /* Address of MustBeInt instruction */
      int regTemp = sqlite3GetTempReg(pParse);

      /* Invoke MustBeInt to coerce the child key value to an integer (i.e.
      ** apply the affinity of the parent key). If this fails, then there
      ** is no matching parent key. Before using MustBeInt, make a copy of
      ** the value. Otherwise, the value inserted into the child key column
      ** will have INTEGER affinity applied to it, which may not be correct.  */
      sqlite3VdbeAddOp2(v, OP_SCopy, aiCol[0]+1+regData, regTemp);
      iMustBeInt = sqlite3VdbeAddOp2(v, OP_MustBeInt, regTemp, 0);
      VdbeCoverage(v);

      /* If the parent table is the same as the child table, and we are about
      ** to increment the constraint-counter (i.e. this is an INSERT operation),
      ** then check if the row being inserted matches itself. If so, do not
      ** increment the constraint-counter.  */
      if( pTab==pFKey->pFrom && nIncr==1 ){
        sqlite3VdbeAddOp3(v, OP_Eq, regData, iOk, regTemp); VdbeCoverage(v);
        sqlite3VdbeChangeP5(v, SQLITE_NOTNULL);
      }

      sqlite3OpenTable(pParse, iCur, iDb, pTab, OP_OpenRead);
      sqlite3VdbeAddOp3(v, OP_NotExists, iCur, 0, regTemp); VdbeCoverage(v);
      sqlite3VdbeGoto(v, iOk);
      sqlite3VdbeJumpHere(v, sqlite3VdbeCurrentAddr(v)-2);
      sqlite3VdbeJumpHere(v, iMustBeInt);
      sqlite3ReleaseTempReg(pParse, regTemp);
    }else{
      int nCol = pFKey->nCol;
      int regTemp = sqlite3GetTempRange(pParse, nCol);
      int regRec = sqlite3GetTempReg(pParse);

      sqlite3VdbeAddOp3(v, OP_OpenRead, iCur, pIdx->tnum, iDb);
      sqlite3VdbeSetP4KeyInfo(pParse, pIdx);
      for(i=0; i<nCol; i++){
        sqlite3VdbeAddOp2(v, OP_Copy, aiCol[i]+1+regData, regTemp+i);
      }

      /* If the parent table is the same as the child table, and we are about
      ** to increment the constraint-counter (i.e. this is an INSERT operation),
      ** then check if the row being inserted matches itself. If so, do not
      ** increment the constraint-counter.
      **
      ** If any of the parent-key values are NULL, then the row cannot match
      ** itself. So set JUMPIFNULL to make sure we do the OP_Found if any
      ** of the parent-key values are NULL (at this point it is known that
      ** none of the child key values are).
      */
      if( pTab==pFKey->pFrom && nIncr==1 ){
        int iJump = sqlite3VdbeCurrentAddr(v) + nCol + 1;
        for(i=0; i<nCol; i++){
          int iChild = aiCol[i]+1+regData;
          int iParent = pIdx->aiColumn[i]+1+regData;
          assert( pIdx->aiColumn[i]>=0 );
          assert( aiCol[i]!=pTab->iPKey );
          if( pIdx->aiColumn[i]==pTab->iPKey ){
            /* The parent key is a composite key that includes the IPK column */
            iParent = regData;
          }
          sqlite3VdbeAddOp3(v, OP_Ne, iChild, iJump, iParent); VdbeCoverage(v);
          sqlite3VdbeChangeP5(v, SQLITE_JUMPIFNULL);
        }
        sqlite3VdbeGoto(v, iOk);
      }

      sqlite3VdbeAddOp4(v, OP_MakeRecord, regTemp, nCol, regRec,
                        sqlite3IndexAffinityStr(pParse->db,pIdx), nCol);
      sqlite3VdbeAddOp4Int(v, OP_Found, iCur, iOk, regRec, 0); VdbeCoverage(v);

      sqlite3ReleaseTempReg(pParse, regRec);
      sqlite3ReleaseTempRange(pParse, regTemp, nCol);
    }
  }

  if( !pFKey->isDeferred && !(pParse->db->flags & SQLITE_DeferFKs)
   && !pParse->pToplevel
   && !pParse->isMultiWrite
  ){
    /* Special case: If this is an INSERT statement that will insert exactly
    ** one row into the table, raise a constraint immediately instead of
    ** incrementing a counter. This is necessary as the VM code is being
    ** generated for will not open a statement transaction.  */
    assert( nIncr==1 );
    sqlite3HaltConstraint(pParse, SQLITE_CONSTRAINT_FOREIGNKEY,
        OE_Abort, 0, P4_STATIC, P5_ConstraintFK);
  }else{
    if( nIncr>0 && pFKey->isDeferred==0 ){
      sqlite3MayAbort(pParse);
    }
    sqlite3VdbeAddOp2(v, OP_FkCounter, pFKey->isDeferred, nIncr);
  }

  sqlite3VdbeResolveLabel(v, iOk);
  sqlite3VdbeAddOp1(v, OP_Close, iCur);
}