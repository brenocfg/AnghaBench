#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* err; TYPE_2__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/ * keyname; int /*<<< orphan*/  genctx; } ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/ * key; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ KEY_LIST ;
typedef  TYPE_2__ KEYGEN_TEST_DATA ;
typedef  TYPE_3__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_keygen (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 scalar_t__ find_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* private_keys ; 

__attribute__((used)) static int keygen_test_run(EVP_TEST *t)
{
    KEYGEN_TEST_DATA *keygen = t->data;
    EVP_PKEY *pkey = NULL;

    t->err = NULL;
    if (EVP_PKEY_keygen(keygen->genctx, &pkey) <= 0) {
        t->err = "KEYGEN_GENERATE_ERROR";
        goto err;
    }

    if (keygen->keyname != NULL) {
        KEY_LIST *key;

        if (find_key(NULL, keygen->keyname, private_keys)) {
            TEST_info("Duplicate key %s", keygen->keyname);
            goto err;
        }

        if (!TEST_ptr(key = OPENSSL_malloc(sizeof(*key))))
            goto err;
        key->name = keygen->keyname;
        keygen->keyname = NULL;
        key->key = pkey;
        key->next = private_keys;
        private_keys = key;
    } else {
        EVP_PKEY_free(pkey);
    }

    return 1;

err:
    EVP_PKEY_free(pkey);
    return 0;
}