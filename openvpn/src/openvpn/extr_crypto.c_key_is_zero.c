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
struct key_type {int cipher_length; } ;
struct key {scalar_t__* cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CRYPT_ERRORS ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
key_is_zero(struct key *key, const struct key_type *kt)
{
    int i;
    for (i = 0; i < kt->cipher_length; ++i)
    {
        if (key->cipher[i])
        {
            return false;
        }
    }
    msg(D_CRYPT_ERRORS, "CRYPTO INFO: WARNING: zero key detected");
    return true;
}