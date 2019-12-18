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
struct key_type {int cipher_length; int hmac_length; scalar_t__ digest; scalar_t__ cipher; } ;
struct key {int /*<<< orphan*/  hmac; int /*<<< orphan*/  cipher; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct key) ; 
 int /*<<< orphan*/  D_SHOW_KEY_SOURCE ; 
 int MAX_CIPHER_KEY_LENGTH ; 
 int MAX_HMAC_KEY_LENGTH ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  check_key (struct key*,struct key_type const*) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixup_key (struct key*,struct key_type const*) ; 
 int /*<<< orphan*/  format_hex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rand_bytes (int /*<<< orphan*/ ,int) ; 

void
generate_key_random(struct key *key, const struct key_type *kt)
{
    int cipher_len = MAX_CIPHER_KEY_LENGTH;
    int hmac_len = MAX_HMAC_KEY_LENGTH;

    struct gc_arena gc = gc_new();

    do
    {
        CLEAR(*key);
        if (kt)
        {
            if (kt->cipher && kt->cipher_length > 0 && kt->cipher_length <= cipher_len)
            {
                cipher_len = kt->cipher_length;
            }

            if (kt->digest && kt->hmac_length > 0 && kt->hmac_length <= hmac_len)
            {
                hmac_len = kt->hmac_length;
            }
        }
        if (!rand_bytes(key->cipher, cipher_len)
            || !rand_bytes(key->hmac, hmac_len))
        {
            msg(M_FATAL, "ERROR: Random number generator cannot obtain entropy for key generation");
        }

        dmsg(D_SHOW_KEY_SOURCE, "Cipher source entropy: %s", format_hex(key->cipher, cipher_len, 0, &gc));
        dmsg(D_SHOW_KEY_SOURCE, "HMAC source entropy: %s", format_hex(key->hmac, hmac_len, 0, &gc));

        if (kt)
        {
            fixup_key(key, kt);
        }
    } while (kt && !check_key(key, kt));

    gc_free(&gc);
}