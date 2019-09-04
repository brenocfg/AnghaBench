#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * next_bio; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (TYPE_1__*) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_set_retry_read (TYPE_1__*) ; 
 scalar_t__ RAND_priv_bytes (unsigned char*,int) ; 

__attribute__((used)) static int nbiof_read(BIO *b, char *out, int outl)
{
    int ret = 0;
    int num;
    unsigned char n;

    if (out == NULL)
        return 0;
    if (b->next_bio == NULL)
        return 0;

    BIO_clear_retry_flags(b);
    if (RAND_priv_bytes(&n, 1) <= 0)
        return -1;
    num = (n & 0x07);

    if (outl > num)
        outl = num;

    if (num == 0) {
        ret = -1;
        BIO_set_retry_read(b);
    } else {
        ret = BIO_read(b->next_bio, out, outl);
        if (ret < 0)
            BIO_copy_next_retry(b);
    }
    return ret;
}