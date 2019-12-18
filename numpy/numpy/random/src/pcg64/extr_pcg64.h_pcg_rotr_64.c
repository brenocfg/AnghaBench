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

/* Variables and functions */
 unsigned int _rotr64 (unsigned int,unsigned int) ; 

__attribute__((used)) static inline uint64_t pcg_rotr_64(uint64_t value, unsigned int rot) {
#ifdef _WIN32
  return _rotr64(value, rot);
#else
  return (value >> rot) | (value << ((-rot) & 63));
#endif
}