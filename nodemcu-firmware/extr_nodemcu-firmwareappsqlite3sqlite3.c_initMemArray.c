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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {scalar_t__ szMalloc; int /*<<< orphan*/  flags; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */

__attribute__((used)) static void initMemArray(Mem *p, int N, sqlite3 *db, u16 flags){
  while( (N--)>0 ){
    p->db = db;
    p->flags = flags;
    p->szMalloc = 0;
#ifdef SQLITE_DEBUG
    p->pScopyFrom = 0;
#endif
    p++;
  }
}