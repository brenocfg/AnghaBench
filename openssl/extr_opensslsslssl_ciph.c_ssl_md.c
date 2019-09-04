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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int SSL_HANDSHAKE_MAC_MASK ; 
 int SSL_MD_NUM_IDX ; 
 int /*<<< orphan*/  const** ssl_digest_methods ; 

const EVP_MD *ssl_md(int idx)
{
    idx &= SSL_HANDSHAKE_MAC_MASK;
    if (idx < 0 || idx >= SSL_MD_NUM_IDX)
        return NULL;
    return ssl_digest_methods[idx];
}