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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_3__ {int /*<<< orphan*/ * extensions; } ;
typedef  int /*<<< orphan*/  OSSL_CRMF_MSG ;
typedef  TYPE_1__ OSSL_CRMF_CERTTEMPLATE ;

/* Variables and functions */
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_MSG_PUSH0_EXTENSION ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* OSSL_CRMF_MSG_get0_tmpl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_EXTENSION_new_null () ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OSSL_CRMF_MSG_push0_extension(OSSL_CRMF_MSG *crm,
                                  X509_EXTENSION *ext)
{
    int new = 0;
    OSSL_CRMF_CERTTEMPLATE *tmpl = OSSL_CRMF_MSG_get0_tmpl(crm);

    if (tmpl == NULL || ext == NULL) { /* also crm == NULL implies this */
        CRMFerr(CRMF_F_OSSL_CRMF_MSG_PUSH0_EXTENSION, CRMF_R_NULL_ARGUMENT);
        return 0;
    }

    if (tmpl->extensions == NULL) {
        if ((tmpl->extensions = sk_X509_EXTENSION_new_null()) == NULL)
            goto err;
        new = 1;
    }

    if (!sk_X509_EXTENSION_push(tmpl->extensions, ext))
        goto err;
    return 1;
 err:
    if (new != 0) {
        sk_X509_EXTENSION_free(tmpl->extensions);
        tmpl->extensions = NULL;
    }
    return 0;
}