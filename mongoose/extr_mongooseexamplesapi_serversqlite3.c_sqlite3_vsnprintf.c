#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {scalar_t__ useMalloc; } ;
typedef  TYPE_1__ StrAccum ;

/* Variables and functions */
 char* sqlite3StrAccumFinish (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VXPrintf (TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

char *sqlite3_vsnprintf(int n, char *zBuf, const char *zFormat, va_list ap){
  StrAccum acc;
  if( n<=0 ) return zBuf;
  sqlite3StrAccumInit(&acc, zBuf, n, 0);
  acc.useMalloc = 0;
  sqlite3VXPrintf(&acc, 0, zFormat, ap);
  return sqlite3StrAccumFinish(&acc);
}