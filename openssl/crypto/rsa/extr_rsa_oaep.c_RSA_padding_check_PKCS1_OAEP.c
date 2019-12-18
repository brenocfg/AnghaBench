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
 int RSA_padding_check_PKCS1_OAEP_mgf1 (unsigned char*,int,unsigned char const*,int,int,unsigned char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int RSA_padding_check_PKCS1_OAEP(unsigned char *to, int tlen,
                                 const unsigned char *from, int flen, int num,
                                 const unsigned char *param, int plen)
{
    return RSA_padding_check_PKCS1_OAEP_mgf1(to, tlen, from, flen, num,
                                             param, plen, NULL, NULL);
}