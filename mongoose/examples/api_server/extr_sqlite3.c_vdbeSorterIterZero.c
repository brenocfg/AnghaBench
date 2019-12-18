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
struct TYPE_4__ {int /*<<< orphan*/  aBuffer; int /*<<< orphan*/  aAlloc; } ;
typedef  TYPE_1__ VdbeSorterIter ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdbeSorterIterZero(sqlite3 *db, VdbeSorterIter *pIter){
  sqlite3DbFree(db, pIter->aAlloc);
  sqlite3DbFree(db, pIter->aBuffer);
  memset(pIter, 0, sizeof(VdbeSorterIter));
}