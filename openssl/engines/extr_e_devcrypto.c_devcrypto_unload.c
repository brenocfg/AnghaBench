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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  close_devcrypto () ; 
 int /*<<< orphan*/  destroy_all_cipher_methods () ; 
 int /*<<< orphan*/  destroy_all_digest_methods () ; 

__attribute__((used)) static int devcrypto_unload(ENGINE *e)
{
    destroy_all_cipher_methods();
#ifdef IMPLEMENT_DIGEST
    destroy_all_digest_methods();
#endif

    close_devcrypto();

    return 1;
}