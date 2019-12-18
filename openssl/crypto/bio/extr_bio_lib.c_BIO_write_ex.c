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

int BIO_write_ex(BIO *b, const void *data, size_t dlen, size_t *written)
{
    int ret;

    ret = bio_write_intern(b, data, dlen, written);

    if (ret > 0)
        ret = 1;
    else
        ret = 0;

    return ret;
}