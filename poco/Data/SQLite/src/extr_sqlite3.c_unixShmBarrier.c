#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unixFile ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_5__ {scalar_t__ xLock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ nolockLock ; 
 int /*<<< orphan*/  sqlite3MemoryBarrier () ; 
 int /*<<< orphan*/  unixEnterMutex () ; 
 scalar_t__ unixFileMutexNotheld (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unixLeaveMutex () ; 

__attribute__((used)) static void unixShmBarrier(
  sqlite3_file *fd                /* Database file holding the shared memory */
){
  UNUSED_PARAMETER(fd);
  sqlite3MemoryBarrier();         /* compiler-defined memory barrier */
  assert( fd->pMethods->xLock==nolockLock 
       || unixFileMutexNotheld((unixFile*)fd) 
  );
  unixEnterMutex();               /* Also mutex, for redundancy */
  unixLeaveMutex();
}