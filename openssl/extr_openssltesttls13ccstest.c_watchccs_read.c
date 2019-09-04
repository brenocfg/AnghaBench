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
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_should_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int watchccs_read(BIO *bio, char *out, int outl)
{
    int ret = 0;
    BIO *next = BIO_next(bio);

    if (outl <= 0)
        return 0;
    if (next == NULL)
        return 0;

    BIO_clear_retry_flags(bio);

    ret = BIO_read(next, out, outl);
    if (ret <= 0 && BIO_should_read(next))
        BIO_set_retry_read(bio);

    return ret;
}