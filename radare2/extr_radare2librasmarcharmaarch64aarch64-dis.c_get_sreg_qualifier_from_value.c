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
typedef  enum aarch64_opnd_qualifier { ____Placeholder_aarch64_opnd_qualifier } aarch64_opnd_qualifier ;
typedef  int aarch64_insn ;

/* Variables and functions */
 int AARCH64_OPND_QLF_S_B ; 
 int aarch64_get_qualifier_standard_value (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline enum aarch64_opnd_qualifier
get_sreg_qualifier_from_value (aarch64_insn value)
{
  enum aarch64_opnd_qualifier qualifier = AARCH64_OPND_QLF_S_B + value;

  assert (value <= 0x4
	  && aarch64_get_qualifier_standard_value (qualifier) == value);
  return qualifier;
}