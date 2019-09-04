#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t** prices; } ;
typedef  TYPE_1__ lzma_length_encoder ;

/* Variables and functions */
 size_t const MATCH_LEN_MIN ; 

__attribute__((used)) static inline uint32_t
get_len_price(const lzma_length_encoder *const lencoder,
		const uint32_t len, const uint32_t pos_state)
{
	// NOTE: Unlike the other price tables, length prices are updated
	// in lzma_encoder.c
	return lencoder->prices[pos_state][len - MATCH_LEN_MIN];
}