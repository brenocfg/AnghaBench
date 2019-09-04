#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ks; } ;
struct TYPE_4__ {int* deslong; } ;
typedef  TYPE_2__ DES_key_schedule ;
typedef  int DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  D_ENCRYPT (int,int,int) ; 
 int ROTATE (int,int) ; 

void DES_encrypt2(DES_LONG *data, DES_key_schedule *ks, int enc)
{
    register DES_LONG l, r, t, u;
    register DES_LONG *s;

    r = data[0];
    l = data[1];

    /*
     * Things have been modified so that the initial rotate is done outside
     * the loop.  This required the DES_SPtrans values in sp.h to be rotated
     * 1 bit to the right. One perl script later and things have a 5% speed
     * up on a sparc2. Thanks to Richard Outerbridge for pointing this out.
     */
    /* clear the top bits on machines with 8byte longs */
    r = ROTATE(r, 29) & 0xffffffffL;
    l = ROTATE(l, 29) & 0xffffffffL;

    s = ks->ks->deslong;
    /*
     * I don't know if it is worth the effort of loop unrolling the inner
     * loop
     */
    if (enc) {
        D_ENCRYPT(l, r, 0);     /* 1 */
        D_ENCRYPT(r, l, 2);     /* 2 */
        D_ENCRYPT(l, r, 4);     /* 3 */
        D_ENCRYPT(r, l, 6);     /* 4 */
        D_ENCRYPT(l, r, 8);     /* 5 */
        D_ENCRYPT(r, l, 10);    /* 6 */
        D_ENCRYPT(l, r, 12);    /* 7 */
        D_ENCRYPT(r, l, 14);    /* 8 */
        D_ENCRYPT(l, r, 16);    /* 9 */
        D_ENCRYPT(r, l, 18);    /* 10 */
        D_ENCRYPT(l, r, 20);    /* 11 */
        D_ENCRYPT(r, l, 22);    /* 12 */
        D_ENCRYPT(l, r, 24);    /* 13 */
        D_ENCRYPT(r, l, 26);    /* 14 */
        D_ENCRYPT(l, r, 28);    /* 15 */
        D_ENCRYPT(r, l, 30);    /* 16 */
    } else {
        D_ENCRYPT(l, r, 30);    /* 16 */
        D_ENCRYPT(r, l, 28);    /* 15 */
        D_ENCRYPT(l, r, 26);    /* 14 */
        D_ENCRYPT(r, l, 24);    /* 13 */
        D_ENCRYPT(l, r, 22);    /* 12 */
        D_ENCRYPT(r, l, 20);    /* 11 */
        D_ENCRYPT(l, r, 18);    /* 10 */
        D_ENCRYPT(r, l, 16);    /* 9 */
        D_ENCRYPT(l, r, 14);    /* 8 */
        D_ENCRYPT(r, l, 12);    /* 7 */
        D_ENCRYPT(l, r, 10);    /* 6 */
        D_ENCRYPT(r, l, 8);     /* 5 */
        D_ENCRYPT(l, r, 6);     /* 4 */
        D_ENCRYPT(r, l, 4);     /* 3 */
        D_ENCRYPT(l, r, 2);     /* 2 */
        D_ENCRYPT(r, l, 0);     /* 1 */
    }
    /* rotate and clear the top bits on machines with 8byte longs */
    data[0] = ROTATE(l, 3) & 0xffffffffL;
    data[1] = ROTATE(r, 3) & 0xffffffffL;
    l = r = t = u = 0;
}