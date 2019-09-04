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
typedef  int /*<<< orphan*/  BIO_ADDR ;

/* Variables and functions */

char *BIO_ADDR_path_string(const BIO_ADDR *ap)
{
#ifdef AF_UNIX
    if (ap->sa.sa_family == AF_UNIX)
        return OPENSSL_strdup(ap->s_un.sun_path);
#endif
    return NULL;
}