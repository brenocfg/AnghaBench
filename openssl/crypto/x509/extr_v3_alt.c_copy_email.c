#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_9__ {scalar_t__ flags; int /*<<< orphan*/ * subject_req; int /*<<< orphan*/ * subject_cert; } ;
typedef  TYPE_2__ X509V3_CTX ;
struct TYPE_8__ {int /*<<< orphan*/ * ia5; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; TYPE_1__ d; } ;
typedef  int /*<<< orphan*/  GENERAL_NAMES ;
typedef  TYPE_3__ GENERAL_NAME ;
typedef  int /*<<< orphan*/  ASN1_IA5STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_IA5STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_STRING_dup (int /*<<< orphan*/ ) ; 
 scalar_t__ CTX_TEST ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  GENERAL_NAME_free (TYPE_3__*) ; 
 TYPE_3__* GENERAL_NAME_new () ; 
 int /*<<< orphan*/  GEN_EMAIL ; 
 int /*<<< orphan*/  NID_pkcs9_emailAddress ; 
 int /*<<< orphan*/  X509V3_F_COPY_EMAIL ; 
 int /*<<< orphan*/  X509V3_R_NO_SUBJECT_DETAILS ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_ENTRY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_ENTRY_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_delete_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
 int X509_NAME_get_index_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * X509_REQ_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_push (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int copy_email(X509V3_CTX *ctx, GENERAL_NAMES *gens, int move_p)
{
    X509_NAME *nm;
    ASN1_IA5STRING *email = NULL;
    X509_NAME_ENTRY *ne;
    GENERAL_NAME *gen = NULL;
    int i = -1;

    if (ctx != NULL && ctx->flags == CTX_TEST)
        return 1;
    if (ctx == NULL
        || (ctx->subject_cert == NULL && ctx->subject_req == NULL)) {
        X509V3err(X509V3_F_COPY_EMAIL, X509V3_R_NO_SUBJECT_DETAILS);
        goto err;
    }
    /* Find the subject name */
    if (ctx->subject_cert)
        nm = X509_get_subject_name(ctx->subject_cert);
    else
        nm = X509_REQ_get_subject_name(ctx->subject_req);

    /* Now add any email address(es) to STACK */
    while ((i = X509_NAME_get_index_by_NID(nm,
                                           NID_pkcs9_emailAddress, i)) >= 0) {
        ne = X509_NAME_get_entry(nm, i);
        email = ASN1_STRING_dup(X509_NAME_ENTRY_get_data(ne));
        if (move_p) {
            X509_NAME_delete_entry(nm, i);
            X509_NAME_ENTRY_free(ne);
            i--;
        }
        if (email == NULL || (gen = GENERAL_NAME_new()) == NULL) {
            X509V3err(X509V3_F_COPY_EMAIL, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        gen->d.ia5 = email;
        email = NULL;
        gen->type = GEN_EMAIL;
        if (!sk_GENERAL_NAME_push(gens, gen)) {
            X509V3err(X509V3_F_COPY_EMAIL, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        gen = NULL;
    }

    return 1;

 err:
    GENERAL_NAME_free(gen);
    ASN1_IA5STRING_free(email);
    return 0;

}