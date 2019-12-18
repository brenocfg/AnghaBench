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
typedef  int uint8_t ;
struct key_type {int cipher_length; int hmac_length; } ;
struct key {int* cipher; int* hmac; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct key) ; 
 int /*<<< orphan*/  D_TLS_ERRORS ; 
 int /*<<< orphan*/  buf_read (struct buffer*,int*,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 

int
read_key(struct key *key, const struct key_type *kt, struct buffer *buf)
{
    uint8_t cipher_length;
    uint8_t hmac_length;

    CLEAR(*key);
    if (!buf_read(buf, &cipher_length, 1))
    {
        goto read_err;
    }
    if (!buf_read(buf, &hmac_length, 1))
    {
        goto read_err;
    }

    if (cipher_length != kt->cipher_length || hmac_length != kt->hmac_length)
    {
        goto key_len_err;
    }

    if (!buf_read(buf, key->cipher, cipher_length))
    {
        goto read_err;
    }
    if (!buf_read(buf, key->hmac, hmac_length))
    {
        goto read_err;
    }

    return 1;

read_err:
    msg(D_TLS_ERRORS, "TLS Error: error reading key from remote");
    return -1;

key_len_err:
    msg(D_TLS_ERRORS,
        "TLS Error: key length mismatch, local cipher/hmac %d/%d, remote cipher/hmac %d/%d",
        kt->cipher_length, kt->hmac_length, cipher_length, hmac_length);
    return 0;
}