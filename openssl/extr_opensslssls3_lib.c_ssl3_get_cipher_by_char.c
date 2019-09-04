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
typedef  long uint32_t ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;

/* Variables and functions */
 long SSL3_CK_CIPHERSUITE_FLAG ; 
 int /*<<< orphan*/  const* ssl3_get_cipher_by_id (long) ; 

const SSL_CIPHER *ssl3_get_cipher_by_char(const unsigned char *p)
{
    return ssl3_get_cipher_by_id(SSL3_CK_CIPHERSUITE_FLAG
                                 | ((uint32_t)p[0] << 8L)
                                 | (uint32_t)p[1]);
}