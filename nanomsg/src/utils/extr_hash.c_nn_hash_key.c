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
typedef  int uint32_t ;

/* Variables and functions */

uint32_t nn_hash_key (uint32_t key)
{
    /*  TODO: This is a randomly chosen hashing function. Give some thought
        to picking a more fitting one. */
    key = (key ^ 61) ^ (key >> 16);
    key += key << 3;
    key = key ^ (key >> 4);
    key = key * 0x27d4eb2d;
    key = key ^ (key >> 15);

    return key;
}