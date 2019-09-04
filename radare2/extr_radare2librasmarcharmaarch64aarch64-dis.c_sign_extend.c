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
typedef  int /*<<< orphan*/  int32_t ;
typedef  unsigned int aarch64_insn ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline int32_t
sign_extend (aarch64_insn value, unsigned i)
{
  uint32_t ret = value;

  assert (i < 32);
  if ((value >> i) & 0x1)
    {
      uint32_t val = (uint32_t)(-1) << i;
      ret = ret | val;
    }
  return (int32_t) ret;
}