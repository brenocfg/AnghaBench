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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/  wc; } ;
typedef  TYPE_1__ WhereOrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3WhereClauseClear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void whereOrInfoDelete(sqlite3 *db, WhereOrInfo *p){
  sqlite3WhereClauseClear(&p->wc);
  sqlite3DbFree(db, p);
}