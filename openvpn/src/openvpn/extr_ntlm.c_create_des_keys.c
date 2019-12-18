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
 int /*<<< orphan*/  key_des_fixup (unsigned char*,int,int) ; 

__attribute__((used)) static void
create_des_keys(const unsigned char *hash, unsigned char *key)
{
    key[0] = hash[0];
    key[1] = ((hash[0] & 1) << 7) | (hash[1] >> 1);
    key[2] = ((hash[1] & 3) << 6) | (hash[2] >> 2);
    key[3] = ((hash[2] & 7) << 5) | (hash[3] >> 3);
    key[4] = ((hash[3] & 15) << 4) | (hash[4] >> 4);
    key[5] = ((hash[4] & 31) << 3) | (hash[5] >> 5);
    key[6] = ((hash[5] & 63) << 2) | (hash[6] >> 6);
    key[7] = ((hash[6] & 127) << 1);
    key_des_fixup(key, 8, 1);
}