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
struct TYPE_3__ {int /*<<< orphan*/  fcb_lock; } ;
typedef  TYPE_1__ device_extension ;

/* Variables and functions */
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline void acquire_fcb_lock_shared(device_extension* Vcb) {
    ExAcquireResourceSharedLite(&Vcb->fcb_lock, true);
}