#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int length; int /*<<< orphan*/  g; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ MDH ;

/* Variables and functions */
 int /*<<< orphan*/  MDH_free (TYPE_1__*) ; 
 TYPE_1__* MDH_new () ; 
 int /*<<< orphan*/  MP_gethex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MP_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_set_w (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  P1024 ; 

__attribute__((used)) static MDH *
DHInit(int nKeyBits)
{
    size_t res;
    MDH *dh = MDH_new();

    if (!dh)
        goto failed;

    MP_new(dh->g);

    if (!dh->g)
        goto failed;

    MP_gethex(dh->p, P1024, res);	/* prime P1024, see dhgroups.h */
    if (!res)
    {
        goto failed;
    }

    MP_set_w(dh->g, 2);	/* base 2 */

    dh->length = nKeyBits;
    return dh;

failed:
    if (dh)
        MDH_free(dh);

    return 0;
}