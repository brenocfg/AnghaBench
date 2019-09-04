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
struct TYPE_3__ {int /*<<< orphan*/  singleRequestExtensions; } ;
typedef  TYPE_1__ OCSP_ONEREQ ;

/* Variables and functions */
 int X509V3_add1_i2d (int /*<<< orphan*/ *,int,void*,int,unsigned long) ; 

int OCSP_ONEREQ_add1_ext_i2d(OCSP_ONEREQ *x, int nid, void *value, int crit,
                             unsigned long flags)
{
    return X509V3_add1_i2d(&x->singleRequestExtensions, nid, value, crit,
                           flags);
}