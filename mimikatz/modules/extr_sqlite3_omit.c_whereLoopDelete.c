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
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  WhereLoop ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  whereLoopClear (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void whereLoopDelete(sqlite3 *db, WhereLoop *p){
  whereLoopClear(db, p);
  sqlite3DbFreeNN(db, p);
}