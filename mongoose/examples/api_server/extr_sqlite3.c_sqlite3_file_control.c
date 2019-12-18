#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pMethods; } ;
typedef  TYPE_1__ sqlite3_file ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Pager ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_FCNTL_FILE_POINTER ; 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3BtreePager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3DbNameToBtree (TYPE_2__*,char const*) ; 
 int sqlite3OsFileControl (TYPE_1__*,int,void*) ; 
 TYPE_1__* sqlite3PagerFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_file_control(sqlite3 *db, const char *zDbName, int op, void *pArg){
  int rc = SQLITE_ERROR;
  Btree *pBtree;

  sqlite3_mutex_enter(db->mutex);
  pBtree = sqlite3DbNameToBtree(db, zDbName);
  if( pBtree ){
    Pager *pPager;
    sqlite3_file *fd;
    sqlite3BtreeEnter(pBtree);
    pPager = sqlite3BtreePager(pBtree);
    assert( pPager!=0 );
    fd = sqlite3PagerFile(pPager);
    assert( fd!=0 );
    if( op==SQLITE_FCNTL_FILE_POINTER ){
      *(sqlite3_file**)pArg = fd;
      rc = SQLITE_OK;
    }else if( fd->pMethods ){
      rc = sqlite3OsFileControl(fd, op, pArg);
    }else{
      rc = SQLITE_NOTFOUND;
    }
    sqlite3BtreeLeave(pBtree);
  }
  sqlite3_mutex_leave(db->mutex);
  return rc;   
}