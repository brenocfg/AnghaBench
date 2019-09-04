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
 int bio_read_intern (int /*<<< orphan*/ *,void*,size_t,size_t*) ; 

int BIO_read(BIO *b, void *data, int dlen)
{
    size_t readbytes;
    int ret;

    if (dlen < 0)
        return 0;

    ret = bio_read_intern(b, data, (size_t)dlen, &readbytes);

    if (ret > 0) {
        /* *readbytes should always be <= dlen */
        ret = (int)readbytes;
    }

    return ret;
}