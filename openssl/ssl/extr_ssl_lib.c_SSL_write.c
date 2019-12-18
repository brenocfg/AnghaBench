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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_F_SSL_WRITE ; 
 int /*<<< orphan*/  SSL_R_BAD_LENGTH ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssl_write_internal (int /*<<< orphan*/ *,void const*,size_t,size_t*) ; 

int SSL_write(SSL *s, const void *buf, int num)
{
    int ret;
    size_t written;

    if (num < 0) {
        SSLerr(SSL_F_SSL_WRITE, SSL_R_BAD_LENGTH);
        return -1;
    }

    ret = ssl_write_internal(s, buf, (size_t)num, &written);

    /*
     * The cast is safe here because ret should be <= INT_MAX because num is
     * <= INT_MAX
     */
    if (ret > 0)
        ret = (int)written;

    return ret;
}