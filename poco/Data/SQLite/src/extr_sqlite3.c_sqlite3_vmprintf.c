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
typedef  int /*<<< orphan*/  zBase ;
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  StrAccum ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MAX_LENGTH ; 
 int /*<<< orphan*/  SQLITE_MISUSE_BKPT ; 
 int SQLITE_PRINT_BUF_SIZE ; 
 char* sqlite3StrAccumFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_initialize () ; 
 int /*<<< orphan*/  sqlite3_str_vappendf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

char *sqlite3_vmprintf(const char *zFormat, va_list ap){
  char *z;
  char zBase[SQLITE_PRINT_BUF_SIZE];
  StrAccum acc;

#ifdef SQLITE_ENABLE_API_ARMOR  
  if( zFormat==0 ){
    (void)SQLITE_MISUSE_BKPT;
    return 0;
  }
#endif
#ifndef SQLITE_OMIT_AUTOINIT
  if( sqlite3_initialize() ) return 0;
#endif
  sqlite3StrAccumInit(&acc, 0, zBase, sizeof(zBase), SQLITE_MAX_LENGTH);
  sqlite3_str_vappendf(&acc, zFormat, ap);
  z = sqlite3StrAccumFinish(&acc);
  return z;
}