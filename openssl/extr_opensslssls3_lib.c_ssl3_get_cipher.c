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
typedef  int /*<<< orphan*/  SSL_CIPHER ;

/* Variables and functions */
 unsigned int SSL3_NUM_CIPHERS ; 
 int /*<<< orphan*/  const* ssl3_ciphers ; 

const SSL_CIPHER *ssl3_get_cipher(unsigned int u)
{
    if (u < SSL3_NUM_CIPHERS)
        return &(ssl3_ciphers[SSL3_NUM_CIPHERS - 1 - u]);
    else
        return NULL;
}