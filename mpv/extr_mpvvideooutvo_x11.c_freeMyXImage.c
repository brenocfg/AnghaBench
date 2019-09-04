#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo {TYPE_1__* x11; } ;
struct priv {int /*<<< orphan*/ ** myximage; TYPE_2__* Shminfo; scalar_t__ Shmem_Flag; struct vo* vo; } ;
struct TYPE_4__ {int /*<<< orphan*/  shmaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XShmDetach (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  shmdt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeMyXImage(struct priv *p, int foo)
{
    struct vo *vo = p->vo;
    if (p->Shmem_Flag) {
        XShmDetach(vo->x11->display, &p->Shminfo[foo]);
        XDestroyImage(p->myximage[foo]);
        shmdt(p->Shminfo[foo].shmaddr);
    } else {
        if (p->myximage[foo])
            XDestroyImage(p->myximage[foo]);
    }
    p->myximage[foo] = NULL;
}