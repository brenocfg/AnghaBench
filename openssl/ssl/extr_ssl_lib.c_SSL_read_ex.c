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
 int ssl_read_internal (int /*<<< orphan*/ *,void*,size_t,size_t*) ; 

int SSL_read_ex(SSL *s, void *buf, size_t num, size_t *readbytes)
{
    int ret = ssl_read_internal(s, buf, num, readbytes);

    if (ret < 0)
        ret = 0;
    return ret;
}