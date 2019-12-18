#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int depth; int auth_level; int /*<<< orphan*/  trust; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  X509_F_X509_VERIFY_PARAM_NEW ; 
 int /*<<< orphan*/  X509_TRUST_DEFAULT ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

X509_VERIFY_PARAM *X509_VERIFY_PARAM_new(void)
{
    X509_VERIFY_PARAM *param;

    param = OPENSSL_zalloc(sizeof(*param));
    if (param == NULL) {
        X509err(X509_F_X509_VERIFY_PARAM_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    param->trust = X509_TRUST_DEFAULT;
    /* param->inh_flags = X509_VP_FLAG_DEFAULT; */
    param->depth = -1;
    param->auth_level = -1; /* -1 means unset, 0 is explicit */
    return param;
}