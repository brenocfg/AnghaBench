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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_READWRITE ; 
 int openDatabase (char const*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 

int sqlite3_open(
  const char *zFilename,
  sqlite3 **ppDb
){
  return openDatabase(zFilename, ppDb,
                      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
}