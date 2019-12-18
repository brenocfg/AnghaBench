#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_4__ {int bInverse; int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ CountCtx ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_1__*) ; 
 scalar_t__ SQLITE_NULL ; 
 TYPE_1__* sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void countInverse(sqlite3_context *ctx, int argc, sqlite3_value **argv){
  CountCtx *p;
  p = sqlite3_aggregate_context(ctx, sizeof(*p));
  /* p is always non-NULL since countStep() will have been called first */
  if( (argc==0 || SQLITE_NULL!=sqlite3_value_type(argv[0])) && ALWAYS(p) ){
    p->n--;
#ifdef SQLITE_DEBUG
    p->bInverse = 1;
#endif
  }
}