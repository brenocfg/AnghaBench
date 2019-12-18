#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* vparams; int /*<<< orphan*/  j; int /*<<< orphan*/  q; int /*<<< orphan*/  g; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ int_dhx942_dh ;
struct TYPE_8__ {scalar_t__ counter; TYPE_4__* seed; } ;
typedef  TYPE_2__ int_dhvparams ;
struct TYPE_10__ {scalar_t__ length; scalar_t__ data; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {scalar_t__ seedlen; scalar_t__ counter; scalar_t__ seed; int /*<<< orphan*/  j; int /*<<< orphan*/  q; int /*<<< orphan*/  g; int /*<<< orphan*/  p; } ;
typedef  TYPE_3__ DH ;
typedef  TYPE_4__ ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_FLAG_BITS_LEFT ; 
 int i2d_int_dhx (TYPE_1__*,unsigned char**) ; 

int i2d_DHxparams(const DH *dh, unsigned char **pp)
{
    int_dhx942_dh dhx;
    int_dhvparams dhv;
    ASN1_BIT_STRING bs;
    dhx.p = dh->p;
    dhx.g = dh->g;
    dhx.q = dh->q;
    dhx.j = dh->j;
    if (dh->counter && dh->seed && dh->seedlen > 0) {
        bs.flags = ASN1_STRING_FLAG_BITS_LEFT;
        bs.data = dh->seed;
        bs.length = dh->seedlen;
        dhv.seed = &bs;
        dhv.counter = dh->counter;
        dhx.vparams = &dhv;
    } else
        dhx.vparams = NULL;

    return i2d_int_dhx(&dhx, pp);
}