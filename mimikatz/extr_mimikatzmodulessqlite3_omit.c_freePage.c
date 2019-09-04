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
struct TYPE_4__ {int /*<<< orphan*/  pgno; int /*<<< orphan*/  pBt; } ;
typedef  TYPE_1__ MemPage ;

/* Variables and functions */
 int SQLITE_OK ; 
 int freePage2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freePage(MemPage *pPage, int *pRC){
  if( (*pRC)==SQLITE_OK ){
    *pRC = freePage2(pPage->pBt, pPage, pPage->pgno);
  }
}