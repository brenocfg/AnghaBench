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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int calc_crc32c (int,int /*<<< orphan*/ *,int) ; 

uint64_t get_extent_data_ref_hash2(uint64_t root, uint64_t objid, uint64_t offset) {
    uint32_t high_crc = 0xffffffff, low_crc = 0xffffffff;

    high_crc = calc_crc32c(high_crc, (uint8_t*)&root, sizeof(uint64_t));
    low_crc = calc_crc32c(low_crc, (uint8_t*)&objid, sizeof(uint64_t));
    low_crc = calc_crc32c(low_crc, (uint8_t*)&offset, sizeof(uint64_t));

    return ((uint64_t)high_crc << 31) ^ (uint64_t)low_crc;
}