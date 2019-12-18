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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int FORMAT_ASN1 ; 
 int /*<<< orphan*/ * PEM_read_bio_SSL_SESSION (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int) ; 
 int /*<<< orphan*/ * d2i_SSL_SESSION_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SSL_SESSION *load_sess_id(char *infile, int format)
{
    SSL_SESSION *x = NULL;
    BIO *in = NULL;

    in = bio_open_default(infile, 'r', format);
    if (in == NULL)
        goto end;
    if (format == FORMAT_ASN1)
        x = d2i_SSL_SESSION_bio(in, NULL);
    else
        x = PEM_read_bio_SSL_SESSION(in, NULL, NULL, NULL);
    if (x == NULL) {
        BIO_printf(bio_err, "unable to load SSL_SESSION\n");
        ERR_print_errors(bio_err);
        goto end;
    }

 end:
    BIO_free(in);
    return x;
}