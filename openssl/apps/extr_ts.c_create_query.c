#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_5__* parameter; int /*<<< orphan*/ * algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  TS_REQ ;
typedef  int /*<<< orphan*/  TS_MSG_IMPRINT ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 TYPE_5__* ASN1_TYPE_new () ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (char*) ; 
 int /*<<< orphan*/  NONCE_LENGTH ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  TS_MSG_IMPRINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_MSG_IMPRINT_new () ; 
 int /*<<< orphan*/  TS_MSG_IMPRINT_set_algo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  TS_MSG_IMPRINT_set_msg (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  TS_REQ_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_REQ_new () ; 
 int /*<<< orphan*/  TS_REQ_set_cert_req (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TS_REQ_set_msg_imprint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_REQ_set_nonce (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_REQ_set_policy_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_REQ_set_version (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  V_ASN1_NULL ; 
 int /*<<< orphan*/  X509_ALGOR_free (TYPE_1__*) ; 
 TYPE_1__* X509_ALGOR_new () ; 
 int /*<<< orphan*/  bio_err ; 
 int create_digest (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,unsigned char**) ; 
 int /*<<< orphan*/ * create_nonce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * txt2obj (char const*) ; 

__attribute__((used)) static TS_REQ *create_query(BIO *data_bio, const char *digest, const EVP_MD *md,
                            const char *policy, int no_nonce, int cert)
{
    int ret = 0;
    TS_REQ *ts_req = NULL;
    int len;
    TS_MSG_IMPRINT *msg_imprint = NULL;
    X509_ALGOR *algo = NULL;
    unsigned char *data = NULL;
    ASN1_OBJECT *policy_obj = NULL;
    ASN1_INTEGER *nonce_asn1 = NULL;

    if (md == NULL && (md = EVP_get_digestbyname("sha256")) == NULL)
        goto err;
    if ((ts_req = TS_REQ_new()) == NULL)
        goto err;
    if (!TS_REQ_set_version(ts_req, 1))
        goto err;
    if ((msg_imprint = TS_MSG_IMPRINT_new()) == NULL)
        goto err;
    if ((algo = X509_ALGOR_new()) == NULL)
        goto err;
    if ((algo->algorithm = OBJ_nid2obj(EVP_MD_type(md))) == NULL)
        goto err;
    if ((algo->parameter = ASN1_TYPE_new()) == NULL)
        goto err;
    algo->parameter->type = V_ASN1_NULL;
    if (!TS_MSG_IMPRINT_set_algo(msg_imprint, algo))
        goto err;
    if ((len = create_digest(data_bio, digest, md, &data)) == 0)
        goto err;
    if (!TS_MSG_IMPRINT_set_msg(msg_imprint, data, len))
        goto err;
    if (!TS_REQ_set_msg_imprint(ts_req, msg_imprint))
        goto err;
    if (policy && (policy_obj = txt2obj(policy)) == NULL)
        goto err;
    if (policy_obj && !TS_REQ_set_policy_id(ts_req, policy_obj))
        goto err;

    /* Setting nonce if requested. */
    if (!no_nonce && (nonce_asn1 = create_nonce(NONCE_LENGTH)) == NULL)
        goto err;
    if (nonce_asn1 && !TS_REQ_set_nonce(ts_req, nonce_asn1))
        goto err;
    if (!TS_REQ_set_cert_req(ts_req, cert))
        goto err;

    ret = 1;
 err:
    if (!ret) {
        TS_REQ_free(ts_req);
        ts_req = NULL;
        BIO_printf(bio_err, "could not create query\n");
        ERR_print_errors(bio_err);
    }
    TS_MSG_IMPRINT_free(msg_imprint);
    X509_ALGOR_free(algo);
    OPENSSL_free(data);
    ASN1_OBJECT_free(policy_obj);
    ASN1_INTEGER_free(nonce_asn1);
    return ts_req;
}