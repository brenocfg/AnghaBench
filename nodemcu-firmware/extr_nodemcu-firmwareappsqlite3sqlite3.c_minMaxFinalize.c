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
struct TYPE_4__ {scalar_t__ flags; } ;
typedef  TYPE_1__ sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_1__*) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void minMaxFinalize(sqlite3_context *context){
  sqlite3_value *pRes;
  pRes = (sqlite3_value *)sqlite3_aggregate_context(context, 0);
  if( pRes ){
    if( pRes->flags ){
      sqlite3_result_value(context, pRes);
    }
    sqlite3VdbeMemRelease(pRes);
  }
}