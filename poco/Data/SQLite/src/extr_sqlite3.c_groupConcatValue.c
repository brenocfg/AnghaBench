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
struct TYPE_3__ {scalar_t__ accError; } ;
typedef  TYPE_1__ sqlite3_str ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_TOOBIG ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error_toobig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 char* sqlite3_str_value (TYPE_1__*) ; 

__attribute__((used)) static void groupConcatValue(sqlite3_context *context){
  sqlite3_str *pAccum;
  pAccum = (sqlite3_str*)sqlite3_aggregate_context(context, 0);
  if( pAccum ){
    if( pAccum->accError==SQLITE_TOOBIG ){
      sqlite3_result_error_toobig(context);
    }else if( pAccum->accError==SQLITE_NOMEM ){
      sqlite3_result_error_nomem(context);
    }else{    
      const char *zText = sqlite3_str_value(pAccum);
      sqlite3_result_text(context, zText, -1, SQLITE_TRANSIENT);
    }
  }
}