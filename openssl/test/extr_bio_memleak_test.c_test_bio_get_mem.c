#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ BUF_MEM ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_get_mem_ptr (TYPE_1__*,TYPE_1__**) ; 
 TYPE_1__* BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUF_MEM_free (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 

__attribute__((used)) static int test_bio_get_mem(void)
{
    int ok = 0;
    BIO *bio = NULL;
    BUF_MEM *bufmem = NULL;

    bio = BIO_new(BIO_s_mem());
    if (!TEST_ptr(bio))
        goto finish;
    if (!TEST_int_eq(BIO_puts(bio, "Hello World\n"), 12))
        goto finish;
    BIO_get_mem_ptr(bio, &bufmem);
    if (!TEST_ptr(bufmem))
        goto finish;
    if (!TEST_int_gt(BIO_set_close(bio, BIO_NOCLOSE), 0))
        goto finish;
    BIO_free(bio);
    bio = NULL;
    if (!TEST_mem_eq(bufmem->data, bufmem->length, "Hello World\n", 12))
        goto finish;
    ok = 1;

finish:
    BIO_free(bio);
    BUF_MEM_free(bufmem);
    return ok;
}