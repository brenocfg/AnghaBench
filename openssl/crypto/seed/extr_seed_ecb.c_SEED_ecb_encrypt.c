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
typedef  int /*<<< orphan*/  SEED_KEY_SCHEDULE ;

/* Variables and functions */
 int /*<<< orphan*/  SEED_decrypt (unsigned char const*,unsigned char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SEED_encrypt (unsigned char const*,unsigned char*,int /*<<< orphan*/  const*) ; 

void SEED_ecb_encrypt(const unsigned char *in, unsigned char *out,
                      const SEED_KEY_SCHEDULE *ks, int enc)
{
    if (enc)
        SEED_encrypt(in, out, ks);
    else
        SEED_decrypt(in, out, ks);
}