#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  xy2d; int /*<<< orphan*/  yplusx; int /*<<< orphan*/  yminusx; } ;
typedef  TYPE_1__ ge_precomp ;

/* Variables and functions */
 int /*<<< orphan*/  cmov (TYPE_1__*,TYPE_1__*,char) ; 
 char equal (char,int) ; 
 int /*<<< orphan*/  fe_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_neg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ge_precomp_0 (TYPE_1__*) ; 
 TYPE_1__** k25519Precomp ; 
 char negative (char) ; 

__attribute__((used)) static void table_select(ge_precomp *t, int pos, signed char b)
{
    ge_precomp minust;
    uint8_t bnegative = negative(b);
    uint8_t babs = b - ((uint8_t)((-bnegative) & b) << 1);

    ge_precomp_0(t);
    cmov(t, &k25519Precomp[pos][0], equal(babs, 1));
    cmov(t, &k25519Precomp[pos][1], equal(babs, 2));
    cmov(t, &k25519Precomp[pos][2], equal(babs, 3));
    cmov(t, &k25519Precomp[pos][3], equal(babs, 4));
    cmov(t, &k25519Precomp[pos][4], equal(babs, 5));
    cmov(t, &k25519Precomp[pos][5], equal(babs, 6));
    cmov(t, &k25519Precomp[pos][6], equal(babs, 7));
    cmov(t, &k25519Precomp[pos][7], equal(babs, 8));
    fe_copy(minust.yplusx, t->yminusx);
    fe_copy(minust.yminusx, t->yplusx);
    fe_neg(minust.xy2d, t->xy2d);
    cmov(t, &minust, bnegative);
}