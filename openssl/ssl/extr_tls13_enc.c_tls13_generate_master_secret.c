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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 size_t EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ssl_handshake_md (int /*<<< orphan*/ *) ; 
 int tls13_generate_secret (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 

int tls13_generate_master_secret(SSL *s, unsigned char *out,
                                 unsigned char *prev, size_t prevlen,
                                 size_t *secret_size)
{
    const EVP_MD *md = ssl_handshake_md(s);

    *secret_size = EVP_MD_size(md);
    /* Calls SSLfatal() if required */
    return tls13_generate_secret(s, md, prev, NULL, 0, out);
}