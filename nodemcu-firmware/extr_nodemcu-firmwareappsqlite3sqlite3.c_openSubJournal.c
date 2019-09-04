#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nStmtSpill; } ;
struct TYPE_4__ {scalar_t__ journalMode; int /*<<< orphan*/  sjfd; int /*<<< orphan*/  pVfs; scalar_t__ subjInMemory; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_JOURNALMODE_MEMORY ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_EXCLUSIVE ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_SUBJOURNAL ; 
 int /*<<< orphan*/  isOpen (int /*<<< orphan*/ ) ; 
 TYPE_2__ sqlite3Config ; 
 int sqlite3JournalOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ; 

__attribute__((used)) static int openSubJournal(Pager *pPager){
  int rc = SQLITE_OK;
  if( !isOpen(pPager->sjfd) ){
    const int flags =  SQLITE_OPEN_SUBJOURNAL | SQLITE_OPEN_READWRITE
      | SQLITE_OPEN_CREATE | SQLITE_OPEN_EXCLUSIVE
      | SQLITE_OPEN_DELETEONCLOSE;
    int nStmtSpill = sqlite3Config.nStmtSpill;
    if( pPager->journalMode==PAGER_JOURNALMODE_MEMORY || pPager->subjInMemory ){
      nStmtSpill = -1;
    }
    rc = sqlite3JournalOpen(pPager->pVfs, 0, pPager->sjfd, flags, nStmtSpill);
  }
  return rc;
}