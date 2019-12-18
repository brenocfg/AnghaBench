#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_UTF16NATIVE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int sqlite3ApiExit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,char*) ; 
 int sqlite3LockAndPrepare (TYPE_1__*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const**) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckOk (TYPE_1__*) ; 
 int sqlite3Utf16ByteLen (void const*,int) ; 
 char* sqlite3Utf16to8 (TYPE_1__*,void const*,int,int /*<<< orphan*/ ) ; 
 int sqlite3Utf8CharLen (char*,int) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sqlite3Prepare16(
  sqlite3 *db,              /* Database handle. */ 
  const void *zSql,         /* UTF-16 encoded SQL statement. */
  int nBytes,               /* Length of zSql in bytes. */
  int saveSqlFlag,          /* True to save SQL text into the sqlite3_stmt */
  sqlite3_stmt **ppStmt,    /* OUT: A pointer to the prepared statement */
  const void **pzTail       /* OUT: End of parsed string */
){
  /* This function currently works by first transforming the UTF-16
  ** encoded string to UTF-8, then invoking sqlite3_prepare(). The
  ** tricky bit is figuring out the pointer to return in *pzTail.
  */
  char *zSql8;
  const char *zTail8 = 0;
  int rc = SQLITE_OK;

  assert( ppStmt );
  *ppStmt = 0;
  if( !sqlite3SafetyCheckOk(db) ){
    return SQLITE_MISUSE_BKPT;
  }
  sqlite3_mutex_enter(db->mutex);
  zSql8 = sqlite3Utf16to8(db, zSql, nBytes, SQLITE_UTF16NATIVE);
  if( zSql8 ){
    rc = sqlite3LockAndPrepare(db, zSql8, -1, saveSqlFlag, 0, ppStmt, &zTail8);
  }

  if( zTail8 && pzTail ){
    /* If sqlite3_prepare returns a tail pointer, we calculate the
    ** equivalent pointer into the UTF-16 string by counting the unicode
    ** characters between zSql8 and zTail8, and then returning a pointer
    ** the same number of characters into the UTF-16 string.
    */
    int chars_parsed = sqlite3Utf8CharLen(zSql8, (int)(zTail8-zSql8));
    *pzTail = (u8 *)zSql + sqlite3Utf16ByteLen(zSql, chars_parsed);
  }
  sqlite3DbFree(db, zSql8); 
  rc = sqlite3ApiExit(db, rc);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}