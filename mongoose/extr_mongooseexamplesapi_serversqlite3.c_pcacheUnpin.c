#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* xUnpin ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_1__ pcache2; } ;
struct TYPE_8__ {int /*<<< orphan*/  pCache; scalar_t__ pPage1; scalar_t__ bPurgeable; } ;
struct TYPE_7__ {int pgno; int /*<<< orphan*/  pPage; TYPE_3__* pCache; } ;
typedef  TYPE_2__ PgHdr ;
typedef  TYPE_3__ PCache ;

/* Variables and functions */
 TYPE_4__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcacheUnpin(PgHdr *p){
  PCache *pCache = p->pCache;
  if( pCache->bPurgeable ){
    if( p->pgno==1 ){
      pCache->pPage1 = 0;
    }
    sqlite3GlobalConfig.pcache2.xUnpin(pCache->pCache, p->pPage, 0);
  }
}