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
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_read_ex (int /*<<< orphan*/ *,char*,size_t,size_t*) ; 

__attribute__((used)) static int tap_read_ex(BIO *b, char *buf, size_t size, size_t *out_size)
{
    BIO *next = BIO_next(b);
    int ret = 0;

    ret = BIO_read_ex(next, buf, size, out_size);
    BIO_clear_retry_flags(b);
    BIO_copy_next_retry(b);
    return ret;
}