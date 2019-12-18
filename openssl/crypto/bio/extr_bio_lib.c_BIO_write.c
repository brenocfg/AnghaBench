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
 int bio_write_intern (int /*<<< orphan*/ *,void const*,size_t,size_t*) ; 

int BIO_write(BIO *b, const void *data, int dlen)
{
    size_t written;
    int ret;

    if (dlen < 0)
        return 0;

    ret = bio_write_intern(b, data, (size_t)dlen, &written);

    if (ret > 0) {
        /* *written should always be <= dlen */
        ret = (int)written;
    }

    return ret;
}