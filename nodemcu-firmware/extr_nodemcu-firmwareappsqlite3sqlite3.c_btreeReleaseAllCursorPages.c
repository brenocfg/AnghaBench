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
struct TYPE_3__ {int iPage; scalar_t__* apPage; } ;
typedef  TYPE_1__ BtCursor ;

/* Variables and functions */
 int /*<<< orphan*/  releasePage (scalar_t__) ; 

__attribute__((used)) static void btreeReleaseAllCursorPages(BtCursor *pCur){
  int i;
  for(i=0; i<=pCur->iPage; i++){
    releasePage(pCur->apPage[i]);
    pCur->apPage[i] = 0;
  }
  pCur->iPage = -1;
}