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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int nWiData; int /*<<< orphan*/ ** apWiData; } ;
typedef  TYPE_1__ Wal ;

/* Variables and functions */
 int SQLITE_OK ; 
 int walIndexPageRealloc (TYPE_1__*,int,int /*<<< orphan*/  volatile**) ; 

__attribute__((used)) static int walIndexPage(
  Wal *pWal,               /* The WAL context */
  int iPage,               /* The page we seek */
  volatile u32 **ppPage    /* Write the page pointer here */
){
  if( pWal->nWiData<=iPage || (*ppPage = pWal->apWiData[iPage])==0 ){
    return walIndexPageRealloc(pWal, iPage, ppPage);
  }
  return SQLITE_OK;
}