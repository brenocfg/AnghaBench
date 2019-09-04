#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_10__ {int r1; int r2; int errCode; int nField; int default_rc; int eqSeen; TYPE_6__* pKeyInfo; TYPE_1__* aMem; } ;
typedef  TYPE_3__ UnpackedRecord ;
struct TYPE_11__ {TYPE_2__* db; } ;
struct TYPE_9__ {scalar_t__ mallocFailed; } ;
struct TYPE_8__ {int flags; int n; int /*<<< orphan*/  z; } ;

/* Variables and functions */
 scalar_t__ CORRUPT_DB ; 
 int MEM_Str ; 
 int MIN (int,int) ; 
 scalar_t__ SQLITE_CORRUPT_BKPT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getVarint32 (int const*,int) ; 
 int memcmp (int const*,int /*<<< orphan*/ ,int) ; 
 int sqlite3VdbeRecordCompareWithSkip (int,void const*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  vdbeAssertFieldCountWithinLimits (int,void const*,TYPE_6__*) ; 
 scalar_t__ vdbeRecordCompareDebug (int,void const*,TYPE_3__*,int) ; 

__attribute__((used)) static int vdbeRecordCompareString(
  int nKey1, const void *pKey1, /* Left key */
  UnpackedRecord *pPKey2        /* Right key */
){
  const u8 *aKey1 = (const u8*)pKey1;
  int serial_type;
  int res;

  assert( pPKey2->aMem[0].flags & MEM_Str );
  vdbeAssertFieldCountWithinLimits(nKey1, pKey1, pPKey2->pKeyInfo);
  getVarint32(&aKey1[1], serial_type);
  if( serial_type<12 ){
    res = pPKey2->r1;      /* (pKey1/nKey1) is a number or a null */
  }else if( !(serial_type & 0x01) ){
    res = pPKey2->r2;      /* (pKey1/nKey1) is a blob */
  }else{
    int nCmp;
    int nStr;
    int szHdr = aKey1[0];

    nStr = (serial_type-12) / 2;
    if( (szHdr + nStr) > nKey1 ){
      pPKey2->errCode = (u8)SQLITE_CORRUPT_BKPT;
      return 0;    /* Corruption */
    }
    nCmp = MIN( pPKey2->aMem[0].n, nStr );
    res = memcmp(&aKey1[szHdr], pPKey2->aMem[0].z, nCmp);

    if( res==0 ){
      res = nStr - pPKey2->aMem[0].n;
      if( res==0 ){
        if( pPKey2->nField>1 ){
          res = sqlite3VdbeRecordCompareWithSkip(nKey1, pKey1, pPKey2, 1);
        }else{
          res = pPKey2->default_rc;
          pPKey2->eqSeen = 1;
        }
      }else if( res>0 ){
        res = pPKey2->r2;
      }else{
        res = pPKey2->r1;
      }
    }else if( res>0 ){
      res = pPKey2->r2;
    }else{
      res = pPKey2->r1;
    }
  }

  assert( vdbeRecordCompareDebug(nKey1, pKey1, pPKey2, res)
       || CORRUPT_DB
       || pPKey2->pKeyInfo->db->mallocFailed
  );
  return res;
}