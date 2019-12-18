#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int iReadOff; int nBuffer; int* aBuffer; } ;
typedef  TYPE_1__ VdbeSorterIter ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ sqlite3GetVarint (int*,int /*<<< orphan*/ *) ; 
 int vdbeSorterIterRead (int /*<<< orphan*/ *,TYPE_1__*,int,int**) ; 

__attribute__((used)) static int vdbeSorterIterVarint(sqlite3 *db, VdbeSorterIter *p, u64 *pnOut){
  int iBuf;

  iBuf = p->iReadOff % p->nBuffer;
  if( iBuf && (p->nBuffer-iBuf)>=9 ){
    p->iReadOff += sqlite3GetVarint(&p->aBuffer[iBuf], pnOut);
  }else{
    u8 aVarint[16], *a;
    int i = 0, rc;
    do{
      rc = vdbeSorterIterRead(db, p, 1, &a);
      if( rc ) return rc;
      aVarint[(i++)&0xf] = a[0];
    }while( (a[0]&0x80)!=0 );
    sqlite3GetVarint(aVarint, pnOut);
  }

  return SQLITE_OK;
}