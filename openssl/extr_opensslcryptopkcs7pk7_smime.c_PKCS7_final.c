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
typedef  int /*<<< orphan*/  PKCS7 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_FINAL ; 
 int /*<<< orphan*/  PKCS7_R_PKCS7_DATASIGN ; 
 int /*<<< orphan*/  PKCS7_dataFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS7_dataInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMIME_crlf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int PKCS7_final(PKCS7 *p7, BIO *data, int flags)
{
    BIO *p7bio;
    int ret = 0;

    if ((p7bio = PKCS7_dataInit(p7, NULL)) == NULL) {
        PKCS7err(PKCS7_F_PKCS7_FINAL, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    SMIME_crlf_copy(data, p7bio, flags);

    (void)BIO_flush(p7bio);

    if (!PKCS7_dataFinal(p7, p7bio)) {
        PKCS7err(PKCS7_F_PKCS7_FINAL, PKCS7_R_PKCS7_DATASIGN);
        goto err;
    }

    ret = 1;

 err:
    BIO_free_all(p7bio);

    return ret;

}