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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MurmurHash3_x64_128 (void const*,size_t,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  MurmurHash3_x86_128 (void const*,size_t,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  MurmurHash3_x86_32 (void const*,size_t,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  seed_value ; 
 size_t strlen (char*) ; 

unsigned int
murmur3_simple(const void *keyptr)
{
    size_t len = strlen((char *)keyptr);
#ifdef __x86_64__
    uint64_t hash[2];
    MurmurHash3_x64_128(keyptr, len, seed_value, hash);
    return (unsigned int)hash[1];
#else
    if (len <= 16) {
        unsigned int hash;
        MurmurHash3_x86_32(keyptr, len, seed_value, &hash);
        return hash;
    }

    unsigned int hash[4];
    MurmurHash3_x86_128(keyptr, len, seed_value, hash);
    return hash[3];
#endif
}