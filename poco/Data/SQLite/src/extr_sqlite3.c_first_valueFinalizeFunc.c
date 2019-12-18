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
struct NthValueCtx {scalar_t__ pValue; } ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_value_free (scalar_t__) ; 

__attribute__((used)) static void first_valueFinalizeFunc(sqlite3_context *pCtx){
  struct NthValueCtx *p;
  p = (struct NthValueCtx*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p && p->pValue ){
    sqlite3_result_value(pCtx, p->pValue);
    sqlite3_value_free(p->pValue);
    p->pValue = 0;
  }
}