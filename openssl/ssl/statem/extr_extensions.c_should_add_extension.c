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
 unsigned int SSL_EXT_CLIENT_HELLO ; 
 unsigned int SSL_EXT_TLS1_3_ONLY ; 
 scalar_t__ SSL_IS_DTLS (int /*<<< orphan*/ *) ; 
 int TLS1_3_VERSION ; 
 int /*<<< orphan*/  extension_is_relevant (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

int should_add_extension(SSL *s, unsigned int extctx, unsigned int thisctx,
                         int max_version)
{
    /* Skip if not relevant for our context */
    if ((extctx & thisctx) == 0)
        return 0;

    /* Check if this extension is defined for our protocol. If not, skip */
    if (!extension_is_relevant(s, extctx, thisctx)
            || ((extctx & SSL_EXT_TLS1_3_ONLY) != 0
                && (thisctx & SSL_EXT_CLIENT_HELLO) != 0
                && (SSL_IS_DTLS(s) || max_version < TLS1_3_VERSION)))
        return 0;

    return 1;
}