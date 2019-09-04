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
struct TYPE_4__ {int* aMap; size_t iReadOff; int nBuffer; int* aBuffer; } ;
typedef  TYPE_1__ PmaReader ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ sqlite3GetVarint (int*,int /*<<< orphan*/ *) ; 
 int vdbePmaReadBlob (TYPE_1__*,int,int**) ; 

__attribute__((used)) static int vdbePmaReadVarint(PmaReader *p, u64 *pnOut){
  int iBuf;

  if( p->aMap ){
    p->iReadOff += sqlite3GetVarint(&p->aMap[p->iReadOff], pnOut);
  }else{
    iBuf = p->iReadOff % p->nBuffer;
    if( iBuf && (p->nBuffer-iBuf)>=9 ){
      p->iReadOff += sqlite3GetVarint(&p->aBuffer[iBuf], pnOut);
    }else{
      u8 aVarint[16], *a;
      int i = 0, rc;
      do{
        rc = vdbePmaReadBlob(p, 1, &a);
        if( rc ) return rc;
        aVarint[(i++)&0xf] = a[0];
      }while( (a[0]&0x80)!=0 );
      sqlite3GetVarint(aVarint, pnOut);
    }
  }

  return SQLITE_OK;
}