#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_11__ {scalar_t__ enc; int (* xCmp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,void const*) ;int /*<<< orphan*/  pUser; } ;
struct TYPE_10__ {scalar_t__ enc; void const* z; int /*<<< orphan*/  n; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Mem ;
typedef  TYPE_2__ CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_Ephem ; 
 int /*<<< orphan*/  MEM_Null ; 
 int /*<<< orphan*/  SQLITE_NOMEM_BKPT ; 
 void* sqlite3ValueText (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeMemInit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemShallowCopy (TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,void const*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static int vdbeCompareMemString(
  const Mem *pMem1,
  const Mem *pMem2,
  const CollSeq *pColl,
  u8 *prcErr                      /* If an OOM occurs, set to SQLITE_NOMEM */
){
  if( pMem1->enc==pColl->enc ){
    /* The strings are already in the correct encoding.  Call the
     ** comparison function directly */
    return pColl->xCmp(pColl->pUser,pMem1->n,pMem1->z,pMem2->n,pMem2->z);
  }else{
    int rc;
    const void *v1, *v2;
    Mem c1;
    Mem c2;
    sqlite3VdbeMemInit(&c1, pMem1->db, MEM_Null);
    sqlite3VdbeMemInit(&c2, pMem1->db, MEM_Null);
    sqlite3VdbeMemShallowCopy(&c1, pMem1, MEM_Ephem);
    sqlite3VdbeMemShallowCopy(&c2, pMem2, MEM_Ephem);
    v1 = sqlite3ValueText((sqlite3_value*)&c1, pColl->enc);
    v2 = sqlite3ValueText((sqlite3_value*)&c2, pColl->enc);
    if( (v1==0 || v2==0) ){
      if( prcErr ) *prcErr = SQLITE_NOMEM_BKPT;
      rc = 0;
    }else{
      rc = pColl->xCmp(pColl->pUser, c1.n, v1, c2.n, v2);
    }
    sqlite3VdbeMemRelease(&c1);
    sqlite3VdbeMemRelease(&c2);
    return rc;
  }
}