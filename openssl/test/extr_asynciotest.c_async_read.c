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
struct async_ctrs {scalar_t__ rctr; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 struct async_ctrs* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_should_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int async_read(BIO *bio, char *out, int outl)
{
    struct async_ctrs *ctrs;
    int ret = 0;
    BIO *next = BIO_next(bio);

    if (outl <= 0)
        return 0;
    if (next == NULL)
        return 0;

    ctrs = BIO_get_data(bio);

    BIO_clear_retry_flags(bio);

    if (ctrs->rctr > 0) {
        ret = BIO_read(next, out, 1);
        if (ret <= 0 && BIO_should_read(next))
            BIO_set_retry_read(bio);
        ctrs->rctr = 0;
    } else {
        ctrs->rctr++;
        BIO_set_retry_read(bio);
    }

    return ret;
}