#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nPage; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ IntegrityCk ;

/* Variables and functions */
 int /*<<< orphan*/  checkAppendMsg (TYPE_1__*,char*,scalar_t__) ; 
 scalar_t__ getPageReferenced (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  setPageReferenced (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int checkRef(IntegrityCk *pCheck, Pgno iPage){
  if( iPage==0 ) return 1;
  if( iPage>pCheck->nPage ){
    checkAppendMsg(pCheck, "invalid page number %d", iPage);
    return 1;
  }
  if( getPageReferenced(pCheck, iPage) ){
    checkAppendMsg(pCheck, "2nd reference to page %d", iPage);
    return 1;
  }
  setPageReferenced(pCheck, iPage);
  return 0;
}