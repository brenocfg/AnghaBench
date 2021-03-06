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
struct TYPE_4__ {int /*<<< orphan*/  crl; int /*<<< orphan*/  x509; } ;
struct TYPE_5__ {int type; TYPE_1__ data; } ;
typedef  TYPE_2__ X509_OBJECT ;

/* Variables and functions */
 int X509_CRL_up_ref (int /*<<< orphan*/ ) ; 
#define  X509_LU_CRL 130 
#define  X509_LU_NONE 129 
#define  X509_LU_X509 128 
 int X509_up_ref (int /*<<< orphan*/ ) ; 

int X509_OBJECT_up_ref_count(X509_OBJECT *a)
{
    switch (a->type) {
    case X509_LU_NONE:
        break;
    case X509_LU_X509:
        return X509_up_ref(a->data.x509);
    case X509_LU_CRL:
        return X509_CRL_up_ref(a->data.crl);
    }
    return 1;
}