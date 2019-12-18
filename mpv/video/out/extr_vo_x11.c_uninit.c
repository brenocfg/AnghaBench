#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vo {TYPE_1__* x11; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  original_image; scalar_t__ gc; scalar_t__* myximage; } ;
struct TYPE_2__ {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  freeMyXImage (struct priv*,int) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_x11_uninit (struct vo*) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *p = vo->priv;
    if (p->myximage[0])
        freeMyXImage(p, 0);
    if (p->myximage[1])
        freeMyXImage(p, 1);
    if (p->gc)
        XFreeGC(vo->x11->display, p->gc);

    talloc_free(p->original_image);

    vo_x11_uninit(vo);
}