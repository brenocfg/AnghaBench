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
 size_t OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cipher_data ; 

__attribute__((used)) static void devcrypto_select_all_ciphers(int *cipher_list)
{
    size_t i;

    for (i = 0; i < OSSL_NELEM(cipher_data); i++)
        cipher_list[i] = 1;
}