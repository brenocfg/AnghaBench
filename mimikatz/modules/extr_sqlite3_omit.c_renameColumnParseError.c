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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {int /*<<< orphan*/  zErrMsg; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void renameColumnParseError(
  sqlite3_context *pCtx, 
  int bPost,
  sqlite3_value *pType,
  sqlite3_value *pObject,
  Parse *pParse
){
  const char *zT = (const char*)sqlite3_value_text(pType);
  const char *zN = (const char*)sqlite3_value_text(pObject);
  char *zErr;

  zErr = sqlite3_mprintf("error in %s %s%s: %s", 
      zT, zN, (bPost ? " after rename" : ""),
      pParse->zErrMsg
  );
  sqlite3_result_error(pCtx, zErr, -1);
  sqlite3_free(zErr);
}