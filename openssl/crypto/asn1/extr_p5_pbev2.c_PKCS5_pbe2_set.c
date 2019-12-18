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
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/ * PKCS5_pbe2_set_iv (int /*<<< orphan*/  const*,int,unsigned char*,int,int /*<<< orphan*/ *,int) ; 

X509_ALGOR *PKCS5_pbe2_set(const EVP_CIPHER *cipher, int iter,
                           unsigned char *salt, int saltlen)
{
    return PKCS5_pbe2_set_iv(cipher, iter, salt, saltlen, NULL, -1);
}