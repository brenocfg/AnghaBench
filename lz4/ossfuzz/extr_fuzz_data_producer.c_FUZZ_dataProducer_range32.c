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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 size_t FUZZ_dataProducer_retrieve32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUZZ_getRange_from_uint32 (size_t const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t FUZZ_dataProducer_range32(FUZZ_dataProducer_t* producer,
    uint32_t min, uint32_t max)
{
    size_t const seed = FUZZ_dataProducer_retrieve32(producer);
    return FUZZ_getRange_from_uint32(seed, min, max);
}