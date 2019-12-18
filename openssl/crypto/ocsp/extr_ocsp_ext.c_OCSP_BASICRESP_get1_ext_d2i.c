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
struct TYPE_4__ {int /*<<< orphan*/  responseExtensions; } ;
struct TYPE_5__ {TYPE_1__ tbsResponseData; } ;
typedef  TYPE_2__ OCSP_BASICRESP ;

/* Variables and functions */
 void* X509V3_get_d2i (int /*<<< orphan*/ ,int,int*,int*) ; 

void *OCSP_BASICRESP_get1_ext_d2i(OCSP_BASICRESP *x, int nid, int *crit,
                                  int *idx)
{
    return X509V3_get_d2i(x->tbsResponseData.responseExtensions, nid, crit,
                          idx);
}