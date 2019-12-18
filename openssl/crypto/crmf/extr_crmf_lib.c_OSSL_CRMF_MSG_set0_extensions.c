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
typedef  int /*<<< orphan*/  X509_EXTENSIONS ;
struct TYPE_3__ {int /*<<< orphan*/ * extensions; } ;
typedef  int /*<<< orphan*/  OSSL_CRMF_MSG ;
typedef  TYPE_1__ OSSL_CRMF_CERTTEMPLATE ;

/* Variables and functions */
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_MSG_SET0_EXTENSIONS ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* OSSL_CRMF_MSG_get0_tmpl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_EXTENSION_free ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sk_X509_EXTENSION_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int OSSL_CRMF_MSG_set0_extensions(OSSL_CRMF_MSG *crm,
                                  X509_EXTENSIONS *exts)
{
    OSSL_CRMF_CERTTEMPLATE *tmpl = OSSL_CRMF_MSG_get0_tmpl(crm);

    if (tmpl == NULL) { /* also crm == NULL implies this */
        CRMFerr(CRMF_F_OSSL_CRMF_MSG_SET0_EXTENSIONS, CRMF_R_NULL_ARGUMENT);
        return 0;
    }

    if (sk_X509_EXTENSION_num(exts) == 0) {
        sk_X509_EXTENSION_free(exts);
        exts = NULL; /* do not include empty extensions list */
    }

    sk_X509_EXTENSION_pop_free(tmpl->extensions, X509_EXTENSION_free);
    tmpl->extensions = exts;
    return 1;
}