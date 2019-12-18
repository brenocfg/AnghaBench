#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* meth; scalar_t__ skip; int /*<<< orphan*/ * err; int /*<<< orphan*/ * reason; int /*<<< orphan*/ * expected_err; int /*<<< orphan*/ * data; int /*<<< orphan*/  s; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  test_clearstanza (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_test(EVP_TEST *t)
{
    test_clearstanza(&t->s);
    ERR_clear_error();
    if (t->data != NULL) {
        if (t->meth != NULL)
            t->meth->cleanup(t);
        OPENSSL_free(t->data);
        t->data = NULL;
    }
    OPENSSL_free(t->expected_err);
    t->expected_err = NULL;
    OPENSSL_free(t->reason);
    t->reason = NULL;

    /* Text literal. */
    t->err = NULL;
    t->skip = 0;
    t->meth = NULL;
}