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
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_3__ {int /*<<< orphan*/  lastRowid; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */

sqlite_int64 sqlite3_last_insert_rowid(sqlite3 *db){
  return db->lastRowid;
}