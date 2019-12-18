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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  unsigned int pcg128_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcg_rotr_64 (unsigned int,unsigned int) ; 

inline uint64_t pcg_output_xsh_rr_128_64(pcg128_t state) {
  return pcg_rotr_64(((state >> 29u) ^ state) >> 58u, state >> 122u);
}