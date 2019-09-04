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
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void row_numberValueFunc(sqlite3_context *pCtx){
  i64 *p = (i64*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  sqlite3_result_int64(pCtx, (p ? *p : 0));
}