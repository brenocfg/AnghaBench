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

/* Variables and functions */

const char *OSSL_default_ciphersuites(void)
{
    return "TLS_AES_256_GCM_SHA384:"
#if !defined(OPENSSL_NO_CHACHA) && !defined(OPENSSL_NO_POLY1305)
           "TLS_CHACHA20_POLY1305_SHA256:"
#endif
           "TLS_AES_128_GCM_SHA256";
}