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
typedef  unsigned int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int pcg_rotr_32 (int,unsigned int) ; 

inline uint32_t pcg_output_xsl_rr_64_32(uint64_t state) {
  return pcg_rotr_32(((uint32_t)(state >> 32u)) ^ (uint32_t)state,
                     state >> 59u);
}