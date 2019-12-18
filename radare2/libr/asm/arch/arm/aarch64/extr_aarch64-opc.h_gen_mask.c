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
typedef  int aarch64_insn ;

/* Variables and functions */

__attribute__((used)) static inline aarch64_insn
gen_mask (int width)
{
  return ((aarch64_insn) 1 << width) - 1;
}