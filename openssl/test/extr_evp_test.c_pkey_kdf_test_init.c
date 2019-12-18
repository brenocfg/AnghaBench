#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int skip; TYPE_1__* data; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ PKEY_KDF_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_derive_init (int /*<<< orphan*/ *) ; 
 int NID_undef ; 
 int OBJ_ln2nid (char const*) ; 
 int OBJ_sn2nid (char const*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkey_kdf_test_init(EVP_TEST *t, const char *name)
{
    PKEY_KDF_DATA *kdata;
    int kdf_nid = OBJ_sn2nid(name);

#ifdef OPENSSL_NO_SCRYPT
    if (strcmp(name, "scrypt") == 0) {
        t->skip = 1;
        return 1;
    }
#endif /* OPENSSL_NO_SCRYPT */

#ifdef OPENSSL_NO_CMS
    if (strcmp(name, "X942KDF") == 0) {
        t->skip = 1;
        return 1;
    }
#endif /* OPENSSL_NO_CMS */

    if (kdf_nid == NID_undef)
        kdf_nid = OBJ_ln2nid(name);

    if (!TEST_ptr(kdata = OPENSSL_zalloc(sizeof(*kdata))))
        return 0;
    kdata->ctx = EVP_PKEY_CTX_new_id(kdf_nid, NULL);
    if (kdata->ctx == NULL) {
        OPENSSL_free(kdata);
        return 0;
    }
    if (EVP_PKEY_derive_init(kdata->ctx) <= 0) {
        EVP_PKEY_CTX_free(kdata->ctx);
        OPENSSL_free(kdata);
        return 0;
    }
    t->data = kdata;
    return 1;
}