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
typedef  int /*<<< orphan*/  RSA ;

/* Variables and functions */
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int* keygen_size ; 
 int /*<<< orphan*/  rsa_sp800_56b_check_keypair (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rsa_sp800_56b_check_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_sp800_56b_check_public (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_sp800_56b_generate_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_sp80056b_keygen(int id)
{
    RSA *key = NULL;
    int ret;
    int sz = keygen_size[id];

    ret = TEST_ptr(key = RSA_new())
          && TEST_true(rsa_sp800_56b_generate_key(key, sz, NULL, NULL))
          && TEST_true(rsa_sp800_56b_check_public(key))
          && TEST_true(rsa_sp800_56b_check_private(key))
          && TEST_true(rsa_sp800_56b_check_keypair(key, NULL, -1, sz));

    RSA_free(key);
    return ret;
}