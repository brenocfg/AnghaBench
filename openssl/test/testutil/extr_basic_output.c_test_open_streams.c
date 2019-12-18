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

/* Variables and functions */
 int BIO_FP_TEXT ; 
 int BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_f_linebuffer () ; 
 int /*<<< orphan*/  BIO_f_tap () ; 
 int /*<<< orphan*/  BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bio_err ; 
 int /*<<< orphan*/ * bio_out ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void test_open_streams(void)
{
    bio_out = BIO_new_fp(stdout, BIO_NOCLOSE | BIO_FP_TEXT);
    bio_err = BIO_new_fp(stderr, BIO_NOCLOSE | BIO_FP_TEXT);
#ifdef __VMS
    bio_out = BIO_push(BIO_new(BIO_f_linebuffer()), bio_out);
    bio_err = BIO_push(BIO_new(BIO_f_linebuffer()), bio_err);
#endif
    bio_err = BIO_push(BIO_new(BIO_f_tap()), bio_err);

    OPENSSL_assert(bio_out != NULL);
    OPENSSL_assert(bio_err != NULL);
}