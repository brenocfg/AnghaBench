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

/* Variables and functions */

inline uint32_t pcg_rotr_32(uint32_t value, unsigned int rot) {
#if PCG_USE_INLINE_ASM && __clang__ && (__x86_64__ || __i386__)
  asm("rorl   %%cl, %0" : "=r"(value) : "0"(value), "c"(rot));
  return value;
#else
  return (value >> rot) | (value << ((-rot) & 31));
#endif
}