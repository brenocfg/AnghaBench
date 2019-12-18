#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  sParse ;
struct TYPE_14__ {int rc; char const* zErrMsg; TYPE_2__* db; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pBt; } ;
typedef  TYPE_3__ Parse ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  sqlite3ErrorWithMsg (TYPE_2__*,int,char*,char const*) ; 
 int sqlite3FindDbName (TYPE_2__*,char const*) ; 
 scalar_t__ sqlite3OpenTempDatabase (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ParserReset (TYPE_3__*) ; 

__attribute__((used)) static Btree *findBtree(sqlite3 *pErrorDb, sqlite3 *pDb, const char *zDb){
  int i = sqlite3FindDbName(pDb, zDb);

  if( i==1 ){
    Parse sParse;
    int rc = 0;
    memset(&sParse, 0, sizeof(sParse));
    sParse.db = pDb;
    if( sqlite3OpenTempDatabase(&sParse) ){
      sqlite3ErrorWithMsg(pErrorDb, sParse.rc, "%s", sParse.zErrMsg);
      rc = SQLITE_ERROR;
    }
    sqlite3DbFree(pErrorDb, sParse.zErrMsg);
    sqlite3ParserReset(&sParse);
    if( rc ){
      return 0;
    }
  }

  if( i<0 ){
    sqlite3ErrorWithMsg(pErrorDb, SQLITE_ERROR, "unknown database %s", zDb);
    return 0;
  }

  return pDb->aDb[i].pBt;
}