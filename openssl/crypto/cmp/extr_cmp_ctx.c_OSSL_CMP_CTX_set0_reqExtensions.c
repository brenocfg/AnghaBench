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
struct TYPE_3__ {int /*<<< orphan*/ * reqExtensions; int /*<<< orphan*/  subjectAltNames; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_MULTIPLE_SAN_SOURCES ; 
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_subject_alt_name ; 
 int /*<<< orphan*/  X509_EXTENSION_free ; 
 scalar_t__ X509v3_get_ext_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sk_GENERAL_NAME_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int OSSL_CMP_CTX_set0_reqExtensions(OSSL_CMP_CTX *ctx, X509_EXTENSIONS *exts)
{
    if (ctx == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }

    if (sk_GENERAL_NAME_num(ctx->subjectAltNames) > 0 && exts != NULL
            && X509v3_get_ext_by_NID(exts, NID_subject_alt_name, -1) >= 0) {
        CMPerr(0, CMP_R_MULTIPLE_SAN_SOURCES);
        return 0;
    }
    sk_X509_EXTENSION_pop_free(ctx->reqExtensions, X509_EXTENSION_free);
    ctx->reqExtensions = exts;
    return 1;
}