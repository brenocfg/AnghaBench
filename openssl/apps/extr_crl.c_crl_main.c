#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509_OBJECT ;
typedef  int /*<<< orphan*/  X509_LOOKUP ;
typedef  int /*<<< orphan*/  X509_CRL ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_TIME_print (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int FORMAT_ASN1 ; 
 int FORMAT_PEM ; 
 int /*<<< orphan*/  NID_crl_number ; 
 int /*<<< orphan*/  OBJ_nid2sn (int /*<<< orphan*/ ) ; 
#define  OPT_BADSIG 156 
#define  OPT_CAFILE 155 
#define  OPT_CAPATH 154 
#define  OPT_CASTORE 153 
#define  OPT_CRLNUMBER 152 
#define  OPT_EOF 151 
#define  OPT_ERR 150 
#define  OPT_FINGERPRINT 149 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
#define  OPT_GENDELTA 148 
#define  OPT_HASH 147 
#define  OPT_HASH_OLD 146 
#define  OPT_HELP 145 
#define  OPT_IN 144 
#define  OPT_INFORM 143 
#define  OPT_ISSUER 142 
#define  OPT_KEY 141 
#define  OPT_KEYFORM 140 
#define  OPT_LASTUPDATE 139 
#define  OPT_MD 138 
#define  OPT_NAMEOPT 137 
#define  OPT_NEXTUPDATE 136 
#define  OPT_NOCAFILE 135 
#define  OPT_NOCAPATH 134 
#define  OPT_NOCASTORE 133 
#define  OPT_NOOUT 132 
#define  OPT_OUT 131 
#define  OPT_OUTFORM 130 
#define  OPT_TEXT 129 
#define  OPT_VERIFY 128 
 int PEM_write_bio_X509_CRL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_CRL_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_CRL_digest (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  X509_CRL_free (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_CRL_get0_lastUpdate (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_CRL_get0_nextUpdate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CRL_get0_signature (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_CRL_get_ext_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CRL_get_issuer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CRL_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int X509_CRL_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_LOOKUP_file () ; 
 int /*<<< orphan*/  X509_LU_X509 ; 
 int /*<<< orphan*/  X509_NAME_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_hash_old (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_OBJECT_get0_X509 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_obj_by_subject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_CTX_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_new () ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_pubkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int) ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  corrupt_signature (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crl_options ; 
 int /*<<< orphan*/  get_nameopt () ; 
 int /*<<< orphan*/  i2a_ASN1_INTEGER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ i2d_X509_CRL_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_crl (char*,int) ; 
 int /*<<< orphan*/ * load_key (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 void* opt_arg () ; 
 int /*<<< orphan*/  opt_format (void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_md (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_unknown () ; 
 int /*<<< orphan*/  print_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nameopt (void*) ; 
 int /*<<< orphan*/ * setup_verify (char const*,int,char const*,int,char const*,int) ; 

int crl_main(int argc, char **argv)
{
    X509_CRL *x = NULL;
    BIO *out = NULL;
    X509_STORE *store = NULL;
    X509_STORE_CTX *ctx = NULL;
    X509_LOOKUP *lookup = NULL;
    X509_OBJECT *xobj = NULL;
    EVP_PKEY *pkey;
    const EVP_MD *digest = EVP_sha1();
    char *infile = NULL, *outfile = NULL, *crldiff = NULL, *keyfile = NULL;
    const char *CAfile = NULL, *CApath = NULL, *CAstore = NULL, *prog;
    OPTION_CHOICE o;
    int hash = 0, issuer = 0, lastupdate = 0, nextupdate = 0, noout = 0;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM, keyformat = FORMAT_PEM;
    int ret = 1, num = 0, badsig = 0, fingerprint = 0, crlnumber = 0;
    int text = 0, do_ver = 0, noCAfile = 0, noCApath = 0, noCAstore = 0;
    int i;
#ifndef OPENSSL_NO_MD5
    int hash_old = 0;
#endif

    prog = opt_init(argc, argv, crl_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(crl_options);
            ret = 0;
            goto end;
        case OPT_INFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &informat))
                goto opthelp;
            break;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUTFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &outformat))
                goto opthelp;
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_KEYFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &keyformat))
                goto opthelp;
            break;
        case OPT_KEY:
            keyfile = opt_arg();
            break;
        case OPT_GENDELTA:
            crldiff = opt_arg();
            break;
        case OPT_CAPATH:
            CApath = opt_arg();
            do_ver = 1;
            break;
        case OPT_CAFILE:
            CAfile = opt_arg();
            do_ver = 1;
            break;
        case OPT_CASTORE:
            CAstore = opt_arg();
            do_ver = 1;
            break;
        case OPT_NOCAPATH:
            noCApath =  1;
            break;
        case OPT_NOCAFILE:
            noCAfile =  1;
            break;
        case OPT_NOCASTORE:
            noCAstore =  1;
            break;
        case OPT_HASH_OLD:
#ifndef OPENSSL_NO_MD5
            hash_old = ++num;
#endif
            break;
        case OPT_VERIFY:
            do_ver = 1;
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_HASH:
            hash = ++num;
            break;
        case OPT_ISSUER:
            issuer = ++num;
            break;
        case OPT_LASTUPDATE:
            lastupdate = ++num;
            break;
        case OPT_NEXTUPDATE:
            nextupdate = ++num;
            break;
        case OPT_NOOUT:
            noout = ++num;
            break;
        case OPT_FINGERPRINT:
            fingerprint = ++num;
            break;
        case OPT_CRLNUMBER:
            crlnumber = ++num;
            break;
        case OPT_BADSIG:
            badsig = 1;
            break;
        case OPT_NAMEOPT:
            if (!set_nameopt(opt_arg()))
                goto opthelp;
            break;
        case OPT_MD:
            if (!opt_md(opt_unknown(), &digest))
                goto opthelp;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    x = load_crl(infile, informat);
    if (x == NULL)
        goto end;

    if (do_ver) {
        if ((store = setup_verify(CAfile, noCAfile, CApath, noCApath,
                                  CAstore, noCAstore)) == NULL)
            goto end;
        lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
        if (lookup == NULL)
            goto end;
        ctx = X509_STORE_CTX_new();
        if (ctx == NULL || !X509_STORE_CTX_init(ctx, store, NULL, NULL)) {
            BIO_printf(bio_err, "Error initialising X509 store\n");
            goto end;
        }

        xobj = X509_STORE_CTX_get_obj_by_subject(ctx, X509_LU_X509,
                                                 X509_CRL_get_issuer(x));
        if (xobj == NULL) {
            BIO_printf(bio_err, "Error getting CRL issuer certificate\n");
            goto end;
        }
        pkey = X509_get_pubkey(X509_OBJECT_get0_X509(xobj));
        X509_OBJECT_free(xobj);
        if (pkey == NULL) {
            BIO_printf(bio_err, "Error getting CRL issuer public key\n");
            goto end;
        }
        i = X509_CRL_verify(x, pkey);
        EVP_PKEY_free(pkey);
        if (i < 0)
            goto end;
        if (i == 0)
            BIO_printf(bio_err, "verify failure\n");
        else
            BIO_printf(bio_err, "verify OK\n");
    }

    if (crldiff) {
        X509_CRL *newcrl, *delta;
        if (!keyfile) {
            BIO_puts(bio_err, "Missing CRL signing key\n");
            goto end;
        }
        newcrl = load_crl(crldiff, informat);
        if (!newcrl)
            goto end;
        pkey = load_key(keyfile, keyformat, 0, NULL, NULL, "CRL signing key");
        if (pkey == NULL) {
            X509_CRL_free(newcrl);
            goto end;
        }
        delta = X509_CRL_diff(x, newcrl, pkey, digest, 0);
        X509_CRL_free(newcrl);
        EVP_PKEY_free(pkey);
        if (delta) {
            X509_CRL_free(x);
            x = delta;
        } else {
            BIO_puts(bio_err, "Error creating delta CRL\n");
            goto end;
        }
    }

    if (badsig) {
        const ASN1_BIT_STRING *sig;

        X509_CRL_get0_signature(x, &sig, NULL);
        corrupt_signature(sig);
    }

    if (num) {
        for (i = 1; i <= num; i++) {
            if (issuer == i) {
                print_name(bio_out, "issuer=", X509_CRL_get_issuer(x),
                           get_nameopt());
            }
            if (crlnumber == i) {
                ASN1_INTEGER *crlnum;
                crlnum = X509_CRL_get_ext_d2i(x, NID_crl_number, NULL, NULL);
                BIO_printf(bio_out, "crlNumber=");
                if (crlnum) {
                    i2a_ASN1_INTEGER(bio_out, crlnum);
                    ASN1_INTEGER_free(crlnum);
                } else
                    BIO_puts(bio_out, "<NONE>");
                BIO_printf(bio_out, "\n");
            }
            if (hash == i) {
                BIO_printf(bio_out, "%08lx\n",
                           X509_NAME_hash(X509_CRL_get_issuer(x)));
            }
#ifndef OPENSSL_NO_MD5
            if (hash_old == i) {
                BIO_printf(bio_out, "%08lx\n",
                           X509_NAME_hash_old(X509_CRL_get_issuer(x)));
            }
#endif
            if (lastupdate == i) {
                BIO_printf(bio_out, "lastUpdate=");
                ASN1_TIME_print(bio_out, X509_CRL_get0_lastUpdate(x));
                BIO_printf(bio_out, "\n");
            }
            if (nextupdate == i) {
                BIO_printf(bio_out, "nextUpdate=");
                if (X509_CRL_get0_nextUpdate(x))
                    ASN1_TIME_print(bio_out, X509_CRL_get0_nextUpdate(x));
                else
                    BIO_printf(bio_out, "NONE");
                BIO_printf(bio_out, "\n");
            }
            if (fingerprint == i) {
                int j;
                unsigned int n;
                unsigned char md[EVP_MAX_MD_SIZE];

                if (!X509_CRL_digest(x, digest, md, &n)) {
                    BIO_printf(bio_err, "out of memory\n");
                    goto end;
                }
                BIO_printf(bio_out, "%s Fingerprint=",
                           OBJ_nid2sn(EVP_MD_type(digest)));
                for (j = 0; j < (int)n; j++) {
                    BIO_printf(bio_out, "%02X%c", md[j], (j + 1 == (int)n)
                               ? '\n' : ':');
                }
            }
        }
    }
    out = bio_open_default(outfile, 'w', outformat);
    if (out == NULL)
        goto end;

    if (text)
        X509_CRL_print_ex(out, x, get_nameopt());

    if (noout) {
        ret = 0;
        goto end;
    }

    if (outformat == FORMAT_ASN1)
        i = (int)i2d_X509_CRL_bio(out, x);
    else
        i = PEM_write_bio_X509_CRL(out, x);
    if (!i) {
        BIO_printf(bio_err, "unable to write CRL\n");
        goto end;
    }
    ret = 0;

 end:
    if (ret != 0)
        ERR_print_errors(bio_err);
    BIO_free_all(out);
    X509_CRL_free(x);
    X509_STORE_CTX_free(ctx);
    X509_STORE_free(store);
    return ret;
}