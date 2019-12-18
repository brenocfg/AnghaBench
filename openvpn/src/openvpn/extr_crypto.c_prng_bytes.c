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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 size_t PRNG_NONCE_RESET_BYTES ; 
 int /*<<< orphan*/  md_full (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int md_kt_size (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int min_int (int,int const) ; 
 int /*<<< orphan*/  nonce_data ; 
 scalar_t__ nonce_md ; 
 scalar_t__ nonce_secret_len ; 
 int /*<<< orphan*/  prng_reset_nonce () ; 
 int /*<<< orphan*/  rand_bytes (int /*<<< orphan*/ *,int) ; 

void
prng_bytes(uint8_t *output, int len)
{
    static size_t processed = 0;

    if (nonce_md)
    {
        const int md_size = md_kt_size(nonce_md);
        while (len > 0)
        {
            const int blen = min_int(len, md_size);
            md_full(nonce_md, nonce_data, md_size + nonce_secret_len, nonce_data);
            memcpy(output, nonce_data, blen);
            output += blen;
            len -= blen;

            /* Ensure that random data is reset regularly */
            processed += blen;
            if (processed > PRNG_NONCE_RESET_BYTES)
            {
                prng_reset_nonce();
                processed = 0;
            }
        }
    }
    else
    {
        ASSERT(rand_bytes(output, len));
    }
}