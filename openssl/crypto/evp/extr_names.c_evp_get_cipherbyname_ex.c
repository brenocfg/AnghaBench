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
typedef  int /*<<< orphan*/  OSSL_NAMEMAP ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_NAME_TYPE_CIPHER_METH ; 
 scalar_t__ OBJ_NAME_get (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_INIT_ADD_ALL_CIPHERS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cipher_from_name ; 
 int /*<<< orphan*/  ossl_namemap_doall_names (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int ossl_namemap_name2num (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * ossl_namemap_stored (int /*<<< orphan*/ *) ; 

const EVP_CIPHER *evp_get_cipherbyname_ex(OPENSSL_CTX *libctx, const char *name)
{
    const EVP_CIPHER *cp;
    OSSL_NAMEMAP *namemap;
    int id;

    if (!OPENSSL_init_crypto(OPENSSL_INIT_ADD_ALL_CIPHERS, NULL))
        return NULL;

    cp = (const EVP_CIPHER *)OBJ_NAME_get(name, OBJ_NAME_TYPE_CIPHER_METH);

    if (cp != NULL)
        return cp;

    /*
     * It's not in the method database, but it might be there under a different
     * name. So we check for aliases in the EVP namemap and try all of those
     * in turn.
     */

    namemap = ossl_namemap_stored(libctx);
    id = ossl_namemap_name2num(namemap, name);
    if (id == 0)
        return NULL;

    ossl_namemap_doall_names(namemap, id, cipher_from_name, &cp);

    return cp;
}