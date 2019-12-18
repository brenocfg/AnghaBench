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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TS_F_TS_CONF_LOAD_KEY ; 
 int /*<<< orphan*/  TS_R_CANNOT_LOAD_KEY ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

EVP_PKEY *TS_CONF_load_key(const char *file, const char *pass)
{
    BIO *key = NULL;
    EVP_PKEY *pkey = NULL;

    if ((key = BIO_new_file(file, "r")) == NULL)
        goto end;
    pkey = PEM_read_bio_PrivateKey(key, NULL, NULL, (char *)pass);
 end:
    if (pkey == NULL)
        TSerr(TS_F_TS_CONF_LOAD_KEY, TS_R_CANNOT_LOAD_KEY);
    BIO_free(key);
    return pkey;
}