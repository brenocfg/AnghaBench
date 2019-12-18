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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 

uint16_t word_of_aligned_array(const uint16_t *aligned_array, uint32_t index)
{
    if ( (((uint32_t)aligned_array) % 4) != 0 )
    {
        NODE_DBG("aligned_array is not 4-byte aligned.\n");
        return 0;
    }
    volatile uint32_t v = ((uint32_t *)aligned_array)[ index / 2 ];
    uint16_t *p = (uint16_t *) (&v);
    return (index % 2 == 0) ? p[ 0 ] : p[ 1 ];
}