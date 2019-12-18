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
typedef  int /*<<< orphan*/  SSL_CONF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

SSL_CONF_CTX *SSL_CONF_CTX_new(void)
{
    SSL_CONF_CTX *ret = OPENSSL_zalloc(sizeof(*ret));

    return ret;
}