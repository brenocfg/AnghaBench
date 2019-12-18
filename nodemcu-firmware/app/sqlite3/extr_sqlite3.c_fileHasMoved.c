#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pId; TYPE_2__* pInode; int /*<<< orphan*/  zPath; } ;
typedef  TYPE_3__ unixFile ;
typedef  scalar_t__ u64 ;
struct stat {scalar_t__ st_ino; } ;
struct TYPE_5__ {scalar_t__ pId; scalar_t__ ino; } ;
struct TYPE_6__ {TYPE_1__ fileId; } ;

/* Variables and functions */
 scalar_t__ osStat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int fileHasMoved(unixFile *pFile){
#if OS_VXWORKS
  return pFile->pInode!=0 && pFile->pId!=pFile->pInode->fileId.pId;
#else
  struct stat buf;
  return pFile->pInode!=0 &&
      (osStat(pFile->zPath, &buf)!=0
         || (u64)buf.st_ino!=pFile->pInode->fileId.ino);
#endif
}