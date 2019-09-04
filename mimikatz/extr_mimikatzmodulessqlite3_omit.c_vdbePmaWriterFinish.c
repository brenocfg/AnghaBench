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
typedef  size_t i64 ;
struct TYPE_4__ {int eFWErr; size_t iBufEnd; size_t iBufStart; size_t iWriteOff; int /*<<< orphan*/ * aBuffer; int /*<<< orphan*/  pFd; } ;
typedef  TYPE_1__ PmaWriter ;

/* Variables and functions */
 scalar_t__ ALWAYS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3OsWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdbePmaWriterFinish(PmaWriter *p, i64 *piEof){
  int rc;
  if( p->eFWErr==0 && ALWAYS(p->aBuffer) && p->iBufEnd>p->iBufStart ){
    p->eFWErr = sqlite3OsWrite(p->pFd, 
        &p->aBuffer[p->iBufStart], p->iBufEnd - p->iBufStart, 
        p->iWriteOff + p->iBufStart
    );
  }
  *piEof = (p->iWriteOff + p->iBufEnd);
  sqlite3_free(p->aBuffer);
  rc = p->eFWErr;
  memset(p, 0, sizeof(PmaWriter));
  return rc;
}