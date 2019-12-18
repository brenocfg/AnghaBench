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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  scalar_t__ i64 ;
struct TYPE_3__ {int approx; int overflow; int /*<<< orphan*/  rSum; int /*<<< orphan*/  iSum; int /*<<< orphan*/  cnt; } ;
typedef  TYPE_1__ SumCtx ;

/* Variables and functions */
 int SQLITE_INTEGER ; 
 int SQLITE_NULL ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3AddInt64 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_value_double (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int sqlite3_value_numeric_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sumStep(sqlite3_context *context, int argc, sqlite3_value **argv){
  SumCtx *p;
  int type;
  assert( argc==1 );
  UNUSED_PARAMETER(argc);
  p = sqlite3_aggregate_context(context, sizeof(*p));
  type = sqlite3_value_numeric_type(argv[0]);
  if( p && type!=SQLITE_NULL ){
    p->cnt++;
    if( type==SQLITE_INTEGER ){
      i64 v = sqlite3_value_int64(argv[0]);
      p->rSum += v;
      if( (p->approx|p->overflow)==0 && sqlite3AddInt64(&p->iSum, v) ){
        p->approx = p->overflow = 1;
      }
    }else{
      p->rSum += sqlite3_value_double(argv[0]);
      p->approx = 1;
    }
  }
}