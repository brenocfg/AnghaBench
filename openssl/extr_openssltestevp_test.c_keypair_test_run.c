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
struct TYPE_5__ {char* err; TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pubk; int /*<<< orphan*/ * privk; } ;
typedef  TYPE_1__ KEYPAIR_TEST_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 int EVP_PKEY_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 

__attribute__((used)) static int keypair_test_run(EVP_TEST *t)
{
    int rv = 0;
    const KEYPAIR_TEST_DATA *pair = t->data;

    if (pair->privk == NULL || pair->pubk == NULL) {
        /*
         * this can only happen if only one of the keys is not set
         * which means that one of them was unsupported while the
         * other isn't: hence a key type mismatch.
         */
        t->err = "KEYPAIR_TYPE_MISMATCH";
        rv = 1;
        goto end;
    }

    if ((rv = EVP_PKEY_cmp(pair->privk, pair->pubk)) != 1 ) {
        if ( 0 == rv ) {
            t->err = "KEYPAIR_MISMATCH";
        } else if ( -1 == rv ) {
            t->err = "KEYPAIR_TYPE_MISMATCH";
        } else if ( -2 == rv ) {
            t->err = "UNSUPPORTED_KEY_COMPARISON";
        } else {
            TEST_error("Unexpected error in key comparison");
            rv = 0;
            goto end;
        }
        rv = 1;
        goto end;
    }

    rv = 1;
    t->err = NULL;

end:
    return rv;
}