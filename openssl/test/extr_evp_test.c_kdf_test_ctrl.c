#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* err; int skip; TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ KDF_DATA ;
typedef  TYPE_2__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_kdf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_settable_ctx_params (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_get_cipherbynid (int) ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int) ; 
 int NID_undef ; 
 int OBJ_ln2nid (char*) ; 
 int OBJ_sn2nid (char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int OSSL_PARAM_allocate_from_text (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int kdf_test_ctrl(EVP_TEST *t, EVP_KDF_CTX *kctx,
                         const char *value)
{
    KDF_DATA *kdata = t->data;
    int rv;
    char *p, *name;
    const OSSL_PARAM *defs = EVP_KDF_settable_ctx_params(EVP_KDF_CTX_kdf(kctx));

    if (!TEST_ptr(name = OPENSSL_strdup(value)))
        return 0;
    p = strchr(name, ':');
    if (p != NULL)
        *p++ = '\0';

    rv = OSSL_PARAM_allocate_from_text(kdata->p, defs, name, p,
                                       p != NULL ? strlen(p) : 0);
    *++kdata->p = OSSL_PARAM_construct_end();
    if (!rv) {
        t->err = "KDF_PARAM_ERROR";
        OPENSSL_free(name);
        return 0;
    }
    if (p != NULL && strcmp(name, "digest") == 0) {
        /* If p has an OID and lookup fails assume disabled algorithm */
        int nid = OBJ_sn2nid(p);

        if (nid == NID_undef)
             nid = OBJ_ln2nid(p);
        if (nid != NID_undef && EVP_get_digestbynid(nid) == NULL)
            t->skip = 1;
    }
    if (p != NULL && strcmp(name, "cipher") == 0) {
        /* If p has an OID and lookup fails assume disabled algorithm */
        int nid = OBJ_sn2nid(p);

        if (nid == NID_undef)
             nid = OBJ_ln2nid(p);
        if (nid != NID_undef && EVP_get_cipherbynid(nid) == NULL)
            t->skip = 1;
    }
    OPENSSL_free(name);
    return 1;
}