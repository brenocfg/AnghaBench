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
 size_t SIPHASH_MAX_DIGEST_SIZE ; 

__attribute__((used)) static size_t siphash_adjust_hash_size(size_t hash_size)
{
    if (hash_size == 0)
        hash_size = SIPHASH_MAX_DIGEST_SIZE;
    return hash_size;
}