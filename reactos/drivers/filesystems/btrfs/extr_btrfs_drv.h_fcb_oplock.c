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
struct TYPE_5__ {scalar_t__ Version; } ;
struct TYPE_6__ {int /*<<< orphan*/  oplock; TYPE_1__ Header; } ;
typedef  TYPE_2__ fcb ;
struct TYPE_7__ {int /*<<< orphan*/  Oplock; } ;
typedef  int /*<<< orphan*/ * POPLOCK ;
typedef  TYPE_3__ FSRTL_ADVANCED_FCB_HEADER_NEW ;

/* Variables and functions */
 scalar_t__ FSRTL_FCB_HEADER_V2 ; 

__attribute__((used)) static __inline POPLOCK fcb_oplock(fcb* fcb) {
    if (fcb->Header.Version >= FSRTL_FCB_HEADER_V2)
        return &((FSRTL_ADVANCED_FCB_HEADER_NEW*)&fcb->Header)->Oplock;
    else
        return &fcb->oplock;
}