#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  pModule; } ;
typedef  TYPE_4__ sqlite3_vtab ;
struct TYPE_19__ {char* zName; } ;
struct TYPE_18__ {int /*<<< orphan*/  nArg; int /*<<< orphan*/  zName; } ;
struct TYPE_17__ {int nField; int /*<<< orphan*/ * aSortOrder; TYPE_9__** aColl; } ;
struct TYPE_11__ {int /*<<< orphan*/  i; } ;
struct TYPE_16__ {int flags; char* z; int /*<<< orphan*/  r; TYPE_1__ u; } ;
struct TYPE_13__ {char* z; TYPE_2__* pVtab; TYPE_6__* pMem; int /*<<< orphan*/ * pReal; int /*<<< orphan*/  i; int /*<<< orphan*/ * pI64; TYPE_8__* pFunc; TYPE_9__* pColl; TYPE_7__* pKeyInfo; } ;
struct TYPE_15__ {int p4type; TYPE_3__ p4; } ;
struct TYPE_12__ {TYPE_4__* pVtab; } ;
typedef  TYPE_5__ Op ;
typedef  TYPE_6__ Mem ;
typedef  TYPE_7__ KeyInfo ;
typedef  TYPE_8__ FuncDef ;
typedef  TYPE_9__ CollSeq ;

/* Variables and functions */
 int MEM_Blob ; 
 int MEM_Int ; 
 int MEM_Null ; 
 int MEM_Real ; 
 int MEM_Str ; 
#define  P4_ADVANCE 139 
#define  P4_COLLSEQ 138 
#define  P4_FUNCDEF 137 
#define  P4_INT32 136 
#define  P4_INT64 135 
#define  P4_INTARRAY 134 
#define  P4_KEYINFO 133 
#define  P4_KEYINFO_STATIC 132 
#define  P4_MEM 131 
#define  P4_REAL 130 
#define  P4_SUBPROGRAM 129 
#define  P4_VTAB 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,...) ; 

__attribute__((used)) static char *displayP4(Op *pOp, char *zTemp, int nTemp){
  char *zP4 = zTemp;
  assert( nTemp>=20 );
  switch( pOp->p4type ){
    case P4_KEYINFO_STATIC:
    case P4_KEYINFO: {
      int i, j;
      KeyInfo *pKeyInfo = pOp->p4.pKeyInfo;
      assert( pKeyInfo->aSortOrder!=0 );
      sqlite3_snprintf(nTemp, zTemp, "keyinfo(%d", pKeyInfo->nField);
      i = sqlite3Strlen30(zTemp);
      for(j=0; j<pKeyInfo->nField; j++){
        CollSeq *pColl = pKeyInfo->aColl[j];
        const char *zColl = pColl ? pColl->zName : "nil";
        int n = sqlite3Strlen30(zColl);
        if( i+n>nTemp-6 ){
          memcpy(&zTemp[i],",...",4);
          break;
        }
        zTemp[i++] = ',';
        if( pKeyInfo->aSortOrder[j] ){
          zTemp[i++] = '-';
        }
        memcpy(&zTemp[i], zColl, n+1);
        i += n;
      }
      zTemp[i++] = ')';
      zTemp[i] = 0;
      assert( i<nTemp );
      break;
    }
    case P4_COLLSEQ: {
      CollSeq *pColl = pOp->p4.pColl;
      sqlite3_snprintf(nTemp, zTemp, "collseq(%.20s)", pColl->zName);
      break;
    }
    case P4_FUNCDEF: {
      FuncDef *pDef = pOp->p4.pFunc;
      sqlite3_snprintf(nTemp, zTemp, "%s(%d)", pDef->zName, pDef->nArg);
      break;
    }
    case P4_INT64: {
      sqlite3_snprintf(nTemp, zTemp, "%lld", *pOp->p4.pI64);
      break;
    }
    case P4_INT32: {
      sqlite3_snprintf(nTemp, zTemp, "%d", pOp->p4.i);
      break;
    }
    case P4_REAL: {
      sqlite3_snprintf(nTemp, zTemp, "%.16g", *pOp->p4.pReal);
      break;
    }
    case P4_MEM: {
      Mem *pMem = pOp->p4.pMem;
      if( pMem->flags & MEM_Str ){
        zP4 = pMem->z;
      }else if( pMem->flags & MEM_Int ){
        sqlite3_snprintf(nTemp, zTemp, "%lld", pMem->u.i);
      }else if( pMem->flags & MEM_Real ){
        sqlite3_snprintf(nTemp, zTemp, "%.16g", pMem->r);
      }else if( pMem->flags & MEM_Null ){
        sqlite3_snprintf(nTemp, zTemp, "NULL");
      }else{
        assert( pMem->flags & MEM_Blob );
        zP4 = "(blob)";
      }
      break;
    }
#ifndef SQLITE_OMIT_VIRTUALTABLE
    case P4_VTAB: {
      sqlite3_vtab *pVtab = pOp->p4.pVtab->pVtab;
      sqlite3_snprintf(nTemp, zTemp, "vtab:%p:%p", pVtab, pVtab->pModule);
      break;
    }
#endif
    case P4_INTARRAY: {
      sqlite3_snprintf(nTemp, zTemp, "intarray");
      break;
    }
    case P4_SUBPROGRAM: {
      sqlite3_snprintf(nTemp, zTemp, "program");
      break;
    }
    case P4_ADVANCE: {
      zTemp[0] = 0;
      break;
    }
    default: {
      zP4 = pOp->p4.z;
      if( zP4==0 ){
        zP4 = zTemp;
        zTemp[0] = 0;
      }
    }
  }
  assert( zP4!=0 );
  return zP4;
}