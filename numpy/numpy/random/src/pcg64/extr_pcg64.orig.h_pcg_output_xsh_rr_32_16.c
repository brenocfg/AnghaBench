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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcg_rotr_16 (unsigned int,unsigned int) ; 

inline uint16_t pcg_output_xsh_rr_32_16(uint32_t state) {
  return pcg_rotr_16(((state >> 10u) ^ state) >> 12u, state >> 28u);
}