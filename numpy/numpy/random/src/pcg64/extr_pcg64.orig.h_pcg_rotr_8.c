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
typedef  unsigned int uint8_t ;

/* Variables and functions */

inline uint8_t pcg_rotr_8(uint8_t value, unsigned int rot) {
/* Unfortunately, clang is kinda pathetic when it comes to properly
 * recognizing idiomatic rotate code, so for clang we actually provide
 * assembler directives (enabled with PCG_USE_INLINE_ASM).  Boo, hiss.
 */
#if PCG_USE_INLINE_ASM && __clang__ && (__x86_64__ || __i386__)
  asm("rorb   %%cl, %0" : "=r"(value) : "0"(value), "c"(rot));
  return value;
#else
  return (value >> rot) | (value << ((-rot) & 7));
#endif
}