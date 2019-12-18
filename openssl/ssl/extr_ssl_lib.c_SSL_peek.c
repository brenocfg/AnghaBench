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
 int /*<<< orphan*/  SSL_F_SSL_PEEK ; 
 int /*<<< orphan*/  SSL_R_BAD_LENGTH ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssl_peek_internal (int /*<<< orphan*/ *,void*,size_t,size_t*) ; 

int SSL_peek(SSL *s, void *buf, int num)
{
    int ret;
    size_t readbytes;

    if (num < 0) {
        SSLerr(SSL_F_SSL_PEEK, SSL_R_BAD_LENGTH);
        return -1;
    }

    ret = ssl_peek_internal(s, buf, (size_t)num, &readbytes);

    /*
     * The cast is safe here because ret should be <= INT_MAX because num is
     * <= INT_MAX
     */
    if (ret > 0)
        ret = (int)readbytes;

    return ret;
}