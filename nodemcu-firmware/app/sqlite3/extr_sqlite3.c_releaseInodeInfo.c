#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ nRef; scalar_t__ pShmNode; struct TYPE_8__* pPrev; struct TYPE_8__* pNext; } ;
typedef  TYPE_1__ unixInodeInfo ;
struct TYPE_9__ {TYPE_1__* pInode; } ;
typedef  TYPE_2__ unixFile ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  closePendingFds (TYPE_2__*) ; 
 TYPE_1__* inodeList ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int unixMutexHeld () ; 

__attribute__((used)) static void releaseInodeInfo(unixFile *pFile){
  unixInodeInfo *pInode = pFile->pInode;
  assert( unixMutexHeld() );
  if( ALWAYS(pInode) ){
    pInode->nRef--;
    if( pInode->nRef==0 ){
      assert( pInode->pShmNode==0 );
      closePendingFds(pFile);
      if( pInode->pPrev ){
        assert( pInode->pPrev->pNext==pInode );
        pInode->pPrev->pNext = pInode->pNext;
      }else{
        assert( inodeList==pInode );
        inodeList = pInode->pNext;
      }
      if( pInode->pNext ){
        assert( pInode->pNext->pPrev==pInode );
        pInode->pNext->pPrev = pInode->pPrev;
      }
      sqlite3_free(pInode);
    }
  }
}