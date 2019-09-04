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
struct TYPE_3__ {int /*<<< orphan*/  extensions; } ;
typedef  TYPE_1__ X509_REVOKED ;

/* Variables and functions */
 void* X509V3_get_d2i (int /*<<< orphan*/ ,int,int*,int*) ; 

void *X509_REVOKED_get_ext_d2i(const X509_REVOKED *x, int nid, int *crit, int *idx)
{
    return X509V3_get_d2i(x->extensions, nid, crit, idx);
}