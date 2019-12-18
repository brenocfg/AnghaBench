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
struct TYPE_3__ {int /*<<< orphan*/  pPCache; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  int /*<<< orphan*/  PgHdr ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3PcacheFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static PgHdr *pager_lookup(Pager *pPager, Pgno pgno){
  PgHdr *p;                         /* Return value */

  /* It is not possible for a call to PcacheFetch() with createFlag==0 to
  ** fail, since no attempt to allocate dynamic memory will be made.
  */
  (void)sqlite3PcacheFetch(pPager->pPCache, pgno, 0, &p);
  return p;
}