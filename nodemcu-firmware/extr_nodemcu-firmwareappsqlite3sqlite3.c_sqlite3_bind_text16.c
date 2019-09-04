#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_UTF16NATIVE ; 
 int bindText (int /*<<< orphan*/ *,int,void const*,int,void (*) (void*),int /*<<< orphan*/ ) ; 

int sqlite3_bind_text16(
  sqlite3_stmt *pStmt,
  int i,
  const void *zData,
  int nData,
  void (*xDel)(void*)
){
  return bindText(pStmt, i, zData, nData, xDel, SQLITE_UTF16NATIVE);
}