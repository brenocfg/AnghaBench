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
 int /*<<< orphan*/  BIO_snprintf (char*,unsigned int,char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,unsigned int) ; 

__attribute__((used)) static unsigned int clnt_psk_callback(SSL *ssl, const char *hint,
                                      char *ident, unsigned int max_ident_len,
                                      unsigned char *psk,
                                      unsigned int max_psk_len)
{
    BIO_snprintf(ident, max_ident_len, "psk");

    if (max_psk_len > 20)
        max_psk_len = 20;
    memset(psk, 0x5a, max_psk_len);

    return max_psk_len;
}