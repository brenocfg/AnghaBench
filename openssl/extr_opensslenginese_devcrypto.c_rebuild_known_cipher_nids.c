#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_register_ciphers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_unregister_ciphers (int /*<<< orphan*/ *) ; 
 size_t OSSL_NELEM (TYPE_1__*) ; 
 TYPE_1__* cipher_data ; 
 scalar_t__ devcrypto_test_cipher (size_t) ; 
 int /*<<< orphan*/ * known_cipher_nids ; 
 scalar_t__ known_cipher_nids_amount ; 

__attribute__((used)) static void rebuild_known_cipher_nids(ENGINE *e)
{
    size_t i;

    for (i = 0, known_cipher_nids_amount = 0; i < OSSL_NELEM(cipher_data); i++) {
        if (devcrypto_test_cipher(i))
            known_cipher_nids[known_cipher_nids_amount++] = cipher_data[i].nid;
    }
    ENGINE_unregister_ciphers(e);
    ENGINE_register_ciphers(e);
}