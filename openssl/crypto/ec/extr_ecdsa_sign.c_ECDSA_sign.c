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
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int ECDSA_sign_ex (int,unsigned char const*,int,unsigned char*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ECDSA_sign(int type, const unsigned char *dgst, int dlen, unsigned char
               *sig, unsigned int *siglen, EC_KEY *eckey)
{
    return ECDSA_sign_ex(type, dgst, dlen, sig, siglen, NULL, NULL, eckey);
}