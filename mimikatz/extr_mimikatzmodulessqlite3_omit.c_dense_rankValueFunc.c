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
struct CallCount {int /*<<< orphan*/  nValue; scalar_t__ nStep; } ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dense_rankValueFunc(sqlite3_context *pCtx){
  struct CallCount *p;
  p = (struct CallCount*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p ){
    if( p->nStep ){
      p->nValue++;
      p->nStep = 0;
    }
    sqlite3_result_int64(pCtx, p->nValue);
  }
}