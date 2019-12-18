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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ sqlite3_context ;

/* Variables and functions */
 scalar_t__ SQLITE_TOOBIG ; 
 scalar_t__ sqlite3VdbeMemSetStr (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,void (*) (void*)) ; 
 int /*<<< orphan*/  sqlite3_result_error_toobig (TYPE_1__*) ; 

__attribute__((used)) static void setResultStrOrError(
  sqlite3_context *pCtx,  /* Function context */
  const char *z,          /* String pointer */
  int n,                  /* Bytes in string, or negative */
  u8 enc,                 /* Encoding of z.  0 for BLOBs */
  void (*xDel)(void*)     /* Destructor function */
){
  if( sqlite3VdbeMemSetStr(&pCtx->s, z, n, enc, xDel)==SQLITE_TOOBIG ){
    sqlite3_result_error_toobig(pCtx);
  }
}