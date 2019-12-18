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
struct TYPE_6__ {TYPE_1__* Vcb; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ fcb ;
struct TYPE_5__ {int /*<<< orphan*/  readonly; } ;
typedef  int /*<<< orphan*/  FAST_IO_POSSIBLE ;

/* Variables and functions */
 int /*<<< orphan*/  FastIoIsNotPossible ; 
 int /*<<< orphan*/  FastIoIsPossible ; 
 int /*<<< orphan*/  FastIoIsQuestionable ; 
 int /*<<< orphan*/  FsRtlAreThereCurrentFileLocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsRtlOplockIsFastIoPossible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcb_oplock (TYPE_2__*) ; 

__attribute__((used)) static __inline FAST_IO_POSSIBLE fast_io_possible(fcb* fcb) {
    if (!FsRtlOplockIsFastIoPossible(fcb_oplock(fcb)))
        return FastIoIsNotPossible;

    if (!FsRtlAreThereCurrentFileLocks(&fcb->lock) && !fcb->Vcb->readonly)
        return FastIoIsPossible;

    return FastIoIsQuestionable;
}