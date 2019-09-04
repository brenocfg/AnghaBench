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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BIO_clear_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (char*,int,char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_bio_rdwr_rdonly(void)
{
    int ok = 0;
    BIO *bio = NULL;
    char data[16];

    bio = BIO_new(BIO_s_mem());
    if (!TEST_ptr(bio))
        goto finish;
    if (!TEST_int_eq(BIO_puts(bio, "Hello World\n"), 12))
        goto finish;

    BIO_set_flags(bio, BIO_FLAGS_MEM_RDONLY);
    if (!TEST_int_eq(BIO_read(bio, data, 16), 12))
        goto finish;
    if (!TEST_mem_eq(data, 12, "Hello World\n", 12))
        goto finish;
    if (!TEST_int_gt(BIO_reset(bio), 0))
        goto finish;

    BIO_clear_flags(bio, BIO_FLAGS_MEM_RDONLY);
    if (!TEST_int_eq(BIO_puts(bio, "Hi!\n"), 4))
        goto finish;
    if (!TEST_int_eq(BIO_read(bio, data, 16), 16))
        goto finish;

    if (!TEST_mem_eq(data, 16, "Hello World\nHi!\n", 16))
        goto finish;

    ok = 1;

finish:
    BIO_free(bio);
    return ok;
}