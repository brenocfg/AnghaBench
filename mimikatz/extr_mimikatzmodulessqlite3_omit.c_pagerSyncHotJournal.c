#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  journalHdr; int /*<<< orphan*/  jfd; int /*<<< orphan*/  noSync; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_SYNC_NORMAL ; 
 int sqlite3OsFileSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sqlite3OsSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pagerSyncHotJournal(Pager *pPager){
  int rc = SQLITE_OK;
  if( !pPager->noSync ){
    rc = sqlite3OsSync(pPager->jfd, SQLITE_SYNC_NORMAL);
  }
  if( rc==SQLITE_OK ){
    rc = sqlite3OsFileSize(pPager->jfd, &pPager->journalHdr);
  }
  return rc;
}