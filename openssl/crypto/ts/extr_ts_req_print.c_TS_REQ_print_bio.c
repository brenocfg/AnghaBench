#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  extensions; scalar_t__ cert_req; int /*<<< orphan*/ * nonce; int /*<<< orphan*/  msg_imprint; } ;
typedef  TYPE_1__ TS_REQ ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TS_ASN1_INTEGER_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_MSG_IMPRINT_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_OBJ_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_REQ_get_policy_id (TYPE_1__*) ; 
 int TS_REQ_get_version (TYPE_1__*) ; 
 int /*<<< orphan*/  TS_ext_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int TS_REQ_print_bio(BIO *bio, TS_REQ *a)
{
    int v;
    ASN1_OBJECT *policy_id;

    if (a == NULL)
        return 0;

    v = TS_REQ_get_version(a);
    BIO_printf(bio, "Version: %d\n", v);

    TS_MSG_IMPRINT_print_bio(bio, a->msg_imprint);

    BIO_printf(bio, "Policy OID: ");
    policy_id = TS_REQ_get_policy_id(a);
    if (policy_id == NULL)
        BIO_printf(bio, "unspecified\n");
    else
        TS_OBJ_print_bio(bio, policy_id);

    BIO_printf(bio, "Nonce: ");
    if (a->nonce == NULL)
        BIO_printf(bio, "unspecified");
    else
        TS_ASN1_INTEGER_print_bio(bio, a->nonce);
    BIO_write(bio, "\n", 1);

    BIO_printf(bio, "Certificate required: %s\n",
               a->cert_req ? "yes" : "no");

    TS_ext_print_bio(bio, a->extensions);

    return 1;
}