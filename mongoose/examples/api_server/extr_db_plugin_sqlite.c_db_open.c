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
typedef  void sqlite3 ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_FULLMUTEX ; 
 int SQLITE_OPEN_READWRITE ; 
 int /*<<< orphan*/  sqlite3_exec (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_open_v2 (char const*,void**,int,int /*<<< orphan*/ *) ; 

void *db_open(const char *db_path) {
  sqlite3 *db = NULL;
  if (sqlite3_open_v2(db_path, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
                                        SQLITE_OPEN_FULLMUTEX,
                      NULL) == SQLITE_OK) {
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS kv(key PRIMARY KEY, val);", 0,
                 0, 0);
  }
  return db;
}