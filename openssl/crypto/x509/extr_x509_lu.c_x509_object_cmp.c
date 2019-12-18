#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  crl; int /*<<< orphan*/  x509; } ;
struct TYPE_6__ {int type; TYPE_1__ data; } ;
typedef  TYPE_2__ X509_OBJECT ;

/* Variables and functions */
 int X509_CRL_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  X509_LU_CRL 130 
#define  X509_LU_NONE 129 
#define  X509_LU_X509 128 
 int X509_subject_name_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x509_object_cmp(const X509_OBJECT *const *a,
                           const X509_OBJECT *const *b)
{
    int ret;

    ret = ((*a)->type - (*b)->type);
    if (ret)
        return ret;
    switch ((*a)->type) {
    case X509_LU_X509:
        ret = X509_subject_name_cmp((*a)->data.x509, (*b)->data.x509);
        break;
    case X509_LU_CRL:
        ret = X509_CRL_cmp((*a)->data.crl, (*b)->data.crl);
        break;
    case X509_LU_NONE:
        /* abort(); */
        return 0;
    }
    return ret;
}