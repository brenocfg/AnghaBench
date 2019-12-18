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
struct TYPE_3__ {int /*<<< orphan*/ * canames; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;

/* Variables and functions */
 int SSL_add_store_cert_subjects_to_stack (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * sk_X509_NAME_new_null () ; 

__attribute__((used)) static int cmd_RequestCAStore(SSL_CONF_CTX *cctx, const char *value)
{
    if (cctx->canames == NULL)
        cctx->canames = sk_X509_NAME_new_null();
    if (cctx->canames == NULL)
        return 0;
    return SSL_add_store_cert_subjects_to_stack(cctx->canames, value);
}