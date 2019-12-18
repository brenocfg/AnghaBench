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
typedef  int /*<<< orphan*/  BUF_MEM ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_mem_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (char*,int) ; 
 int /*<<< orphan*/  BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (char*,int,char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_bio_new_mem_buf(void)
{
    int ok = 0;
    BIO *bio;
    BUF_MEM *bufmem;
    char data[16];

    bio = BIO_new_mem_buf("Hello World\n", 12);
    if (!TEST_ptr(bio))
        goto finish;
    if (!TEST_int_eq(BIO_read(bio, data, 5), 5))
        goto finish;
    if (!TEST_mem_eq(data, 5, "Hello", 5))
        goto finish;
    if (!TEST_int_gt(BIO_get_mem_ptr(bio, &bufmem), 0))
        goto finish;
    if (!TEST_int_lt(BIO_write(bio, "test", 4), 0))
        goto finish;
    if (!TEST_int_eq(BIO_read(bio, data, 16), 7))
        goto finish;
    if (!TEST_mem_eq(data, 7, " World\n", 7))
        goto finish;
    if (!TEST_int_gt(BIO_reset(bio), 0))
        goto finish;
    if (!TEST_int_eq(BIO_read(bio, data, 16), 12))
        goto finish;
    if (!TEST_mem_eq(data, 12, "Hello World\n", 12))
        goto finish;
    ok = 1;

finish:
    BIO_free(bio);
    return ok;
}