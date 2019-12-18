#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct RenameCtx {int /*<<< orphan*/  nList; TYPE_1__* pList; } ;
struct TYPE_5__ {TYPE_1__* pRename; } ;
struct TYPE_4__ {void* p; struct TYPE_4__* pNext; } ;
typedef  TYPE_1__ RenameToken ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void renameTokenFind(Parse *pParse, struct RenameCtx *pCtx, void *pPtr){
  RenameToken **pp;
  assert( pPtr!=0 );
  for(pp=&pParse->pRename; (*pp); pp=&(*pp)->pNext){
    if( (*pp)->p==pPtr ){
      RenameToken *pToken = *pp;
      *pp = pToken->pNext;
      pToken->pNext = pCtx->pList;
      pCtx->pList = pToken;
      pCtx->nList++;
      break;
    }
  }
}