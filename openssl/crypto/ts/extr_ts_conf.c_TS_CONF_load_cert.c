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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_AUX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_F_TS_CONF_LOAD_CERT ; 
 int /*<<< orphan*/  TS_R_CANNOT_LOAD_CERT ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

X509 *TS_CONF_load_cert(const char *file)
{
    BIO *cert = NULL;
    X509 *x = NULL;

    if ((cert = BIO_new_file(file, "r")) == NULL)
        goto end;
    x = PEM_read_bio_X509_AUX(cert, NULL, NULL, NULL);
 end:
    if (x == NULL)
        TSerr(TS_F_TS_CONF_LOAD_CERT, TS_R_CANNOT_LOAD_CERT);
    BIO_free(cert);
    return x;
}