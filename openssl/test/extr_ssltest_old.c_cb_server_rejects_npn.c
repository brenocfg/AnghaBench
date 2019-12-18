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
 int SSL_TLSEXT_ERR_NOACK ; 

__attribute__((used)) static int cb_server_rejects_npn(SSL *s, const unsigned char **data,
                                 unsigned int *len, void *arg)
{
    return SSL_TLSEXT_ERR_NOACK;
}