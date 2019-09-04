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
struct LastValueCtx {scalar_t__ pVal; int /*<<< orphan*/  nVal; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_free (scalar_t__) ; 

__attribute__((used)) static void last_valueStepFunc(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **apArg
){
  struct LastValueCtx *p;
  UNUSED_PARAMETER(nArg);
  p = (struct LastValueCtx*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p ){
    sqlite3_value_free(p->pVal);
    p->pVal = sqlite3_value_dup(apArg[0]);
    if( p->pVal==0 ){
      sqlite3_result_error_nomem(pCtx);
    }else{
      p->nVal++;
    }
  }
}