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
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*,int,char const*,int) ; 

__attribute__((used)) static void resolveOutOfRangeError(
  Parse *pParse,         /* The error context into which to write the error */
  const char *zType,     /* "ORDER" or "GROUP" */
  int i,                 /* The index (1-based) of the term out of range */
  int mx                 /* Largest permissible value of i */
){
  sqlite3ErrorMsg(pParse, 
    "%r %s BY term out of range - should be "
    "between 1 and %d", i, zType, mx);
}