#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_22__ {int ex_flags; int ex_pathlen; int ex_pcpathlen; int ex_kusage; int ex_nscert; int /*<<< orphan*/  lock; void* rfc3779_asid; void* rfc3779_addr; void* nc; void* altname; void* akid; void* skid; scalar_t__ ex_xkusage; int /*<<< orphan*/  sha1_hash; } ;
typedef  TYPE_1__ X509 ;
struct TYPE_26__ {int length; int* data; } ;
struct TYPE_25__ {TYPE_20__* pathlen; scalar_t__ ca; } ;
struct TYPE_24__ {TYPE_20__* pcPathLengthConstraint; } ;
struct TYPE_23__ {scalar_t__ type; } ;
typedef  TYPE_2__ PROXY_CERT_INFO_EXTENSION ;
typedef  int /*<<< orphan*/  EXTENDED_KEY_USAGE ;
typedef  TYPE_3__ BASIC_CONSTRAINTS ;
typedef  TYPE_4__ ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_BIT_STRING_free (TYPE_4__*) ; 
 void* ASN1_INTEGER_get (TYPE_20__*) ; 
 int /*<<< orphan*/  ASN1_OBJECT_free ; 
 int /*<<< orphan*/  BASIC_CONSTRAINTS_free (TYPE_3__*) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int EXFLAG_BCONS ; 
 int EXFLAG_CA ; 
 int EXFLAG_CRITICAL ; 
 int EXFLAG_FRESHEST ; 
 int EXFLAG_INVALID ; 
 int EXFLAG_KUSAGE ; 
 int EXFLAG_NSCERT ; 
 int EXFLAG_PROXY ; 
 int EXFLAG_SET ; 
 int EXFLAG_SI ; 
 int EXFLAG_SS ; 
 int EXFLAG_V1 ; 
 int EXFLAG_XKUSAGE ; 
 int /*<<< orphan*/  KU_KEY_CERT_SIGN ; 
#define  NID_OCSP_sign 137 
#define  NID_anyExtendedKeyUsage 136 
 int /*<<< orphan*/  NID_authority_key_identifier ; 
 int /*<<< orphan*/  NID_basic_constraints ; 
#define  NID_client_auth 135 
#define  NID_code_sign 134 
#define  NID_dvcs 133 
#define  NID_email_protect 132 
 int /*<<< orphan*/  NID_ext_key_usage ; 
 int NID_freshest_crl ; 
 int /*<<< orphan*/  NID_issuer_alt_name ; 
 int /*<<< orphan*/  NID_key_usage ; 
#define  NID_ms_sgc 131 
 int /*<<< orphan*/  NID_name_constraints ; 
 int /*<<< orphan*/  NID_netscape_cert_type ; 
#define  NID_ns_sgc 130 
 int /*<<< orphan*/  NID_proxyCertInfo ; 
 int /*<<< orphan*/  NID_sbgp_autonomousSysNum ; 
 int /*<<< orphan*/  NID_sbgp_ipAddrBlock ; 
#define  NID_server_auth 129 
 int /*<<< orphan*/  NID_subject_alt_name ; 
 int /*<<< orphan*/  NID_subject_key_identifier ; 
#define  NID_time_stamp 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROXY_CERT_INFO_EXTENSION_free (TYPE_2__*) ; 
 scalar_t__ V_ASN1_NEG_INTEGER ; 
 int /*<<< orphan*/  X509_EXTENSION_get_critical (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_EXTENSION_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ X509_V_OK ; 
 scalar_t__ X509_check_akid (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  X509_digest (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_ext (TYPE_1__*,int) ; 
 scalar_t__ X509_get_ext_by_NID (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int X509_get_ext_count (TYPE_1__*) ; 
 void* X509_get_ext_d2i (TYPE_1__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_issuer_name (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_get_subject_name (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_get_version (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_supported_extension (int /*<<< orphan*/ *) ; 
 scalar_t__ XKU_ANYEKU ; 
 scalar_t__ XKU_CODE_SIGN ; 
 scalar_t__ XKU_DVCS ; 
 scalar_t__ XKU_OCSP_SIGN ; 
 scalar_t__ XKU_SGC ; 
 scalar_t__ XKU_SMIME ; 
 scalar_t__ XKU_SSL_CLIENT ; 
 scalar_t__ XKU_SSL_SERVER ; 
 scalar_t__ XKU_TIMESTAMP ; 
 int /*<<< orphan*/  ku_reject (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_crldp (TYPE_1__*) ; 
 int sk_ASN1_OBJECT_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  x509_init_sig_info (TYPE_1__*) ; 

__attribute__((used)) static void x509v3_cache_extensions(X509 *x)
{
    BASIC_CONSTRAINTS *bs;
    PROXY_CERT_INFO_EXTENSION *pci;
    ASN1_BIT_STRING *usage;
    ASN1_BIT_STRING *ns;
    EXTENDED_KEY_USAGE *extusage;
    X509_EXTENSION *ex;
    int i;

#ifdef tsan_ld_acq
    /* fast lock-free check, see end of the function for details. */
    if (tsan_ld_acq((TSAN_QUALIFIER int *)&x->ex_cached))
        return;
#endif

    CRYPTO_THREAD_write_lock(x->lock);
    if (x->ex_flags & EXFLAG_SET) {
        CRYPTO_THREAD_unlock(x->lock);
        return;
    }

    X509_digest(x, EVP_sha1(), x->sha1_hash, NULL);
    /* V1 should mean no extensions ... */
    if (!X509_get_version(x))
        x->ex_flags |= EXFLAG_V1;
    /* Handle basic constraints */
    if ((bs = X509_get_ext_d2i(x, NID_basic_constraints, NULL, NULL))) {
        if (bs->ca)
            x->ex_flags |= EXFLAG_CA;
        if (bs->pathlen) {
            if ((bs->pathlen->type == V_ASN1_NEG_INTEGER)
                || !bs->ca) {
                x->ex_flags |= EXFLAG_INVALID;
                x->ex_pathlen = 0;
            } else
                x->ex_pathlen = ASN1_INTEGER_get(bs->pathlen);
        } else
            x->ex_pathlen = -1;
        BASIC_CONSTRAINTS_free(bs);
        x->ex_flags |= EXFLAG_BCONS;
    }
    /* Handle proxy certificates */
    if ((pci = X509_get_ext_d2i(x, NID_proxyCertInfo, NULL, NULL))) {
        if (x->ex_flags & EXFLAG_CA
            || X509_get_ext_by_NID(x, NID_subject_alt_name, -1) >= 0
            || X509_get_ext_by_NID(x, NID_issuer_alt_name, -1) >= 0) {
            x->ex_flags |= EXFLAG_INVALID;
        }
        if (pci->pcPathLengthConstraint) {
            x->ex_pcpathlen = ASN1_INTEGER_get(pci->pcPathLengthConstraint);
        } else
            x->ex_pcpathlen = -1;
        PROXY_CERT_INFO_EXTENSION_free(pci);
        x->ex_flags |= EXFLAG_PROXY;
    }
    /* Handle key usage */
    if ((usage = X509_get_ext_d2i(x, NID_key_usage, NULL, NULL))) {
        if (usage->length > 0) {
            x->ex_kusage = usage->data[0];
            if (usage->length > 1)
                x->ex_kusage |= usage->data[1] << 8;
        } else
            x->ex_kusage = 0;
        x->ex_flags |= EXFLAG_KUSAGE;
        ASN1_BIT_STRING_free(usage);
    }
    x->ex_xkusage = 0;
    if ((extusage = X509_get_ext_d2i(x, NID_ext_key_usage, NULL, NULL))) {
        x->ex_flags |= EXFLAG_XKUSAGE;
        for (i = 0; i < sk_ASN1_OBJECT_num(extusage); i++) {
            switch (OBJ_obj2nid(sk_ASN1_OBJECT_value(extusage, i))) {
            case NID_server_auth:
                x->ex_xkusage |= XKU_SSL_SERVER;
                break;

            case NID_client_auth:
                x->ex_xkusage |= XKU_SSL_CLIENT;
                break;

            case NID_email_protect:
                x->ex_xkusage |= XKU_SMIME;
                break;

            case NID_code_sign:
                x->ex_xkusage |= XKU_CODE_SIGN;
                break;

            case NID_ms_sgc:
            case NID_ns_sgc:
                x->ex_xkusage |= XKU_SGC;
                break;

            case NID_OCSP_sign:
                x->ex_xkusage |= XKU_OCSP_SIGN;
                break;

            case NID_time_stamp:
                x->ex_xkusage |= XKU_TIMESTAMP;
                break;

            case NID_dvcs:
                x->ex_xkusage |= XKU_DVCS;
                break;

            case NID_anyExtendedKeyUsage:
                x->ex_xkusage |= XKU_ANYEKU;
                break;
            }
        }
        sk_ASN1_OBJECT_pop_free(extusage, ASN1_OBJECT_free);
    }

    if ((ns = X509_get_ext_d2i(x, NID_netscape_cert_type, NULL, NULL))) {
        if (ns->length > 0)
            x->ex_nscert = ns->data[0];
        else
            x->ex_nscert = 0;
        x->ex_flags |= EXFLAG_NSCERT;
        ASN1_BIT_STRING_free(ns);
    }
    x->skid = X509_get_ext_d2i(x, NID_subject_key_identifier, NULL, NULL);
    x->akid = X509_get_ext_d2i(x, NID_authority_key_identifier, NULL, NULL);
    /* Does subject name match issuer ? */
    if (!X509_NAME_cmp(X509_get_subject_name(x), X509_get_issuer_name(x))) {
        x->ex_flags |= EXFLAG_SI;
        /* If SKID matches AKID also indicate self signed */
        if (X509_check_akid(x, x->akid) == X509_V_OK &&
            !ku_reject(x, KU_KEY_CERT_SIGN))
            x->ex_flags |= EXFLAG_SS;
    }
    x->altname = X509_get_ext_d2i(x, NID_subject_alt_name, NULL, NULL);
    x->nc = X509_get_ext_d2i(x, NID_name_constraints, &i, NULL);
    if (!x->nc && (i != -1))
        x->ex_flags |= EXFLAG_INVALID;
    setup_crldp(x);

#ifndef OPENSSL_NO_RFC3779
    x->rfc3779_addr = X509_get_ext_d2i(x, NID_sbgp_ipAddrBlock, NULL, NULL);
    x->rfc3779_asid = X509_get_ext_d2i(x, NID_sbgp_autonomousSysNum,
                                       NULL, NULL);
#endif
    for (i = 0; i < X509_get_ext_count(x); i++) {
        ex = X509_get_ext(x, i);
        if (OBJ_obj2nid(X509_EXTENSION_get_object(ex))
            == NID_freshest_crl)
            x->ex_flags |= EXFLAG_FRESHEST;
        if (!X509_EXTENSION_get_critical(ex))
            continue;
        if (!X509_supported_extension(ex)) {
            x->ex_flags |= EXFLAG_CRITICAL;
            break;
        }
    }
    x509_init_sig_info(x);
    x->ex_flags |= EXFLAG_SET;
#ifdef tsan_st_rel
    tsan_st_rel((TSAN_QUALIFIER int *)&x->ex_cached, 1);
    /*
     * Above store triggers fast lock-free check in the beginning of the
     * function. But one has to ensure that the structure is "stable", i.e.
     * all stores are visible on all processors. Hence the release fence.
     */
#endif
    CRYPTO_THREAD_unlock(x->lock);
}