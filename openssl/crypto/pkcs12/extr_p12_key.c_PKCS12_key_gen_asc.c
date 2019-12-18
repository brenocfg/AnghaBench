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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_asc2uni (char const*,int,unsigned char**,int*) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_KEY_GEN_ASC ; 
 int PKCS12_key_gen_uni (unsigned char*,int,unsigned char*,int,int,int,int,unsigned char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PKCS12_key_gen_asc(const char *pass, int passlen, unsigned char *salt,
                       int saltlen, int id, int iter, int n,
                       unsigned char *out, const EVP_MD *md_type)
{
    int ret;
    unsigned char *unipass;
    int uniplen;

    if (pass == NULL) {
        unipass = NULL;
        uniplen = 0;
    } else if (!OPENSSL_asc2uni(pass, passlen, &unipass, &uniplen)) {
        PKCS12err(PKCS12_F_PKCS12_KEY_GEN_ASC, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    ret = PKCS12_key_gen_uni(unipass, uniplen, salt, saltlen,
                             id, iter, n, out, md_type);
    if (ret <= 0)
        return 0;
    OPENSSL_clear_free(unipass, uniplen);
    return ret;
}