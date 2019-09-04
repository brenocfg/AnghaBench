#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {int /*<<< orphan*/ * certs; } ;
typedef  int OPTION_CHOICE ;
typedef  TYPE_1__ NETSCAPE_CERT_SEQUENCE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_PEM ; 
 int /*<<< orphan*/  NETSCAPE_CERT_SEQUENCE_free (TYPE_1__*) ; 
 TYPE_1__* NETSCAPE_CERT_SEQUENCE_new () ; 
#define  OPT_EOF 133 
#define  OPT_ERR 132 
#define  OPT_HELP 131 
#define  OPT_IN 130 
#define  OPT_OUT 129 
#define  OPT_TOSEQ 128 
 TYPE_1__* PEM_read_bio_NETSCAPE_CERT_SEQUENCE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_NETSCAPE_CERT_SEQUENCE (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PEM_write_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_cert_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nseq_options ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/ * sk_X509_new_null () ; 
 int sk_X509_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_X509_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_value (int /*<<< orphan*/ *,int) ; 

int nseq_main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL;
    X509 *x509 = NULL;
    NETSCAPE_CERT_SEQUENCE *seq = NULL;
    OPTION_CHOICE o;
    int toseq = 0, ret = 1, i;
    char *infile = NULL, *outfile = NULL, *prog;

    prog = opt_init(argc, argv, nseq_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            ret = 0;
            opt_help(nseq_options);
            goto end;
        case OPT_TOSEQ:
            toseq = 1;
            break;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    in = bio_open_default(infile, 'r', FORMAT_PEM);
    if (in == NULL)
        goto end;
    out = bio_open_default(outfile, 'w', FORMAT_PEM);
    if (out == NULL)
        goto end;

    if (toseq) {
        seq = NETSCAPE_CERT_SEQUENCE_new();
        if (seq == NULL)
            goto end;
        seq->certs = sk_X509_new_null();
        if (seq->certs == NULL)
            goto end;
        while ((x509 = PEM_read_bio_X509(in, NULL, NULL, NULL)))
            sk_X509_push(seq->certs, x509);

        if (!sk_X509_num(seq->certs)) {
            BIO_printf(bio_err, "%s: Error reading certs file %s\n",
                       prog, infile);
            ERR_print_errors(bio_err);
            goto end;
        }
        PEM_write_bio_NETSCAPE_CERT_SEQUENCE(out, seq);
        ret = 0;
        goto end;
    }

    seq = PEM_read_bio_NETSCAPE_CERT_SEQUENCE(in, NULL, NULL, NULL);
    if (seq == NULL) {
        BIO_printf(bio_err, "%s: Error reading sequence file %s\n",
                   prog, infile);
        ERR_print_errors(bio_err);
        goto end;
    }

    for (i = 0; i < sk_X509_num(seq->certs); i++) {
        x509 = sk_X509_value(seq->certs, i);
        dump_cert_text(out, x509);
        PEM_write_bio_X509(out, x509);
    }
    ret = 0;
 end:
    BIO_free(in);
    BIO_free_all(out);
    NETSCAPE_CERT_SEQUENCE_free(seq);

    return ret;
}