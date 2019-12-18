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
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int do_test_bio_cipher (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_bio_enc_aes_128_cbc(int idx)
{
    return do_test_bio_cipher(EVP_aes_128_cbc(), idx);
}