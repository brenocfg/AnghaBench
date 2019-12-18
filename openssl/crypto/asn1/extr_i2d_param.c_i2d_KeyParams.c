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
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int (* param_encode ) (TYPE_2__ const*,unsigned char**) ;} ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_I2D_KEYPARAMS ; 
 int /*<<< orphan*/  ASN1_R_UNSUPPORTED_TYPE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__ const*,unsigned char**) ; 

int i2d_KeyParams(const EVP_PKEY *a, unsigned char **pp)
{
    if (a->ameth != NULL && a->ameth->param_encode != NULL)
        return a->ameth->param_encode(a, pp);
    ASN1err(ASN1_F_I2D_KEYPARAMS, ASN1_R_UNSUPPORTED_TYPE);
    return -1;
}