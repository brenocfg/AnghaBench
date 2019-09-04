#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int skip; char* err; TYPE_1__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/ * keyname; struct TYPE_10__* genctx; } ;
typedef  TYPE_1__ KEYGEN_TEST_DATA ;
typedef  TYPE_2__ EVP_TEST ;
typedef  TYPE_1__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTX_free (TYPE_1__*) ; 
 TYPE_1__* EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_keygen_init (TYPE_1__*) ; 
 int NID_undef ; 
 int OBJ_ln2nid (char const*) ; 
 int OBJ_sn2nid (char const*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 

__attribute__((used)) static int keygen_test_init(EVP_TEST *t, const char *alg)
{
    KEYGEN_TEST_DATA *data;
    EVP_PKEY_CTX *genctx;
    int nid = OBJ_sn2nid(alg);

    if (nid == NID_undef) {
        nid = OBJ_ln2nid(alg);
        if (nid == NID_undef)
            return 0;
    }

    if (!TEST_ptr(genctx = EVP_PKEY_CTX_new_id(nid, NULL))) {
        /* assume algorithm disabled */
        t->skip = 1;
        return 1;
    }

    if (EVP_PKEY_keygen_init(genctx) <= 0) {
        t->err = "KEYGEN_INIT_ERROR";
        goto err;
    }

    if (!TEST_ptr(data = OPENSSL_malloc(sizeof(*data))))
        goto err;
    data->genctx = genctx;
    data->keyname = NULL;
    t->data = data;
    t->err = NULL;
    return 1;

err:
    EVP_PKEY_CTX_free(genctx);
    return 0;
}