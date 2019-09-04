#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int iDb; } ;
struct TYPE_10__ {TYPE_1__ init; scalar_t__ mallocFailed; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_11__ {int nQueryLoop; char* zErrMsg; scalar_t__ pNewTable; scalar_t__ pNewIndex; scalar_t__ pNewTrigger; TYPE_2__* db; int /*<<< orphan*/  eParseMode; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_MODE_RENAME_COLUMN ; 
 int /*<<< orphan*/  PARSE_MODE_RENAME_TABLE ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3FindDbName (TYPE_2__*,char const*) ; 
 int sqlite3RunParser (TYPE_3__*,char const*,char**) ; 

__attribute__((used)) static int renameParseSql(
  Parse *p,                       /* Memory to use for Parse object */
  const char *zDb,                /* Name of schema SQL belongs to */
  int bTable,                     /* 1 -> RENAME TABLE, 0 -> RENAME COLUMN */
  sqlite3 *db,                    /* Database handle */
  const char *zSql,               /* SQL to parse */
  int bTemp                       /* True if SQL is from temp schema */
){
  int rc;
  char *zErr = 0;

  db->init.iDb = bTemp ? 1 : sqlite3FindDbName(db, zDb);

  /* Parse the SQL statement passed as the first argument. If no error
  ** occurs and the parse does not result in a new table, index or
  ** trigger object, the database must be corrupt. */
  memset(p, 0, sizeof(Parse));
  p->eParseMode = (bTable ? PARSE_MODE_RENAME_TABLE : PARSE_MODE_RENAME_COLUMN);
  p->db = db;
  p->nQueryLoop = 1;
  rc = sqlite3RunParser(p, zSql, &zErr);
  assert( p->zErrMsg==0 );
  assert( rc!=SQLITE_OK || zErr==0 );
  p->zErrMsg = zErr;
  if( db->mallocFailed ) rc = SQLITE_NOMEM;
  if( rc==SQLITE_OK 
   && p->pNewTable==0 && p->pNewIndex==0 && p->pNewTrigger==0 
  ){
    rc = SQLITE_CORRUPT_BKPT;
  }

#ifdef SQLITE_DEBUG
  /* Ensure that all mappings in the Parse.pRename list really do map to
  ** a part of the input string.  */
  if( rc==SQLITE_OK ){
    int nSql = sqlite3Strlen30(zSql);
    RenameToken *pToken;
    for(pToken=p->pRename; pToken; pToken=pToken->pNext){
      assert( pToken->t.z>=zSql && &pToken->t.z[pToken->t.n]<=&zSql[nSql] );
    }
  }
#endif

  db->init.iDb = 0;
  return rc;
}