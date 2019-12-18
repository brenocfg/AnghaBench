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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_FATAL ; 
 int md_kt_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__* nonce_data ; 
 int /*<<< orphan*/  nonce_md ; 
 int nonce_secret_len ; 
 int /*<<< orphan*/  rand_bytes (scalar_t__*,int const) ; 

__attribute__((used)) static void
prng_reset_nonce(void)
{
    const int size = md_kt_size(nonce_md) + nonce_secret_len;
#if 1 /* Must be 1 for real usage */
    if (!rand_bytes(nonce_data, size))
    {
        msg(M_FATAL, "ERROR: Random number generator cannot obtain entropy for PRNG");
    }
#else
    /* Only for testing -- will cause a predictable PRNG sequence */
    {
        int i;
        for (i = 0; i < size; ++i)
        {
            nonce_data[i] = (uint8_t) i;
        }
    }
#endif
}