#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_9__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int i64 ;
struct TYPE_10__ {int iBufEnd; int iBufStart; int iWriteOff; int nBuffer; int /*<<< orphan*/ * pFile; int /*<<< orphan*/  eFWErr; int /*<<< orphan*/ * aBuffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  pBt; } ;
typedef  TYPE_3__ FileWriter ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_NOMEM ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3BtreeGetPageSize (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3DbMallocRaw (TYPE_2__*,int) ; 

__attribute__((used)) static void fileWriterInit(
  sqlite3 *db,                    /* Database (for malloc) */
  sqlite3_file *pFile,            /* File to write to */
  FileWriter *p,                  /* Object to populate */
  i64 iStart                      /* Offset of pFile to begin writing at */
){
  int nBuf = sqlite3BtreeGetPageSize(db->aDb[0].pBt);

  memset(p, 0, sizeof(FileWriter));
  p->aBuffer = (u8 *)sqlite3DbMallocRaw(db, nBuf);
  if( !p->aBuffer ){
    p->eFWErr = SQLITE_NOMEM;
  }else{
    p->iBufEnd = p->iBufStart = (iStart % nBuf);
    p->iWriteOff = iStart - p->iBufStart;
    p->nBuffer = nBuf;
    p->pFile = pFile;
  }
}