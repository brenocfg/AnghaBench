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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_3__ {scalar_t__ pPragma; int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_1__ PragmaVtabCursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  pragmaVtabCursorClear (TYPE_1__*) ; 
 int sqlite3_finalize (scalar_t__) ; 
 scalar_t__ sqlite3_step (scalar_t__) ; 

__attribute__((used)) static int pragmaVtabNext(sqlite3_vtab_cursor *pVtabCursor){
  PragmaVtabCursor *pCsr = (PragmaVtabCursor*)pVtabCursor;
  int rc = SQLITE_OK;

  /* Increment the xRowid value */
  pCsr->iRowid++;
  assert( pCsr->pPragma );
  if( SQLITE_ROW!=sqlite3_step(pCsr->pPragma) ){
    rc = sqlite3_finalize(pCsr->pPragma);
    pCsr->pPragma = 0;
    pragmaVtabCursorClear(pCsr);
  }
  return rc;
}