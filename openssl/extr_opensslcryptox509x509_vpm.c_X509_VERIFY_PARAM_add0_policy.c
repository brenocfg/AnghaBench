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
struct TYPE_3__ {scalar_t__ policies; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ sk_ASN1_OBJECT_new_null () ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_push (scalar_t__,int /*<<< orphan*/ *) ; 

int X509_VERIFY_PARAM_add0_policy(X509_VERIFY_PARAM *param,
                                  ASN1_OBJECT *policy)
{
    if (!param->policies) {
        param->policies = sk_ASN1_OBJECT_new_null();
        if (!param->policies)
            return 0;
    }
    if (!sk_ASN1_OBJECT_push(param->policies, policy))
        return 0;
    return 1;
}