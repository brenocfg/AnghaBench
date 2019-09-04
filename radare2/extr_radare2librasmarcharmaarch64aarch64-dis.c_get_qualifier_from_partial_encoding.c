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
 int AARCH64_MAX_QLF_SEQ_NUM ; 
 int const AARCH64_OPND_QLF_NIL ; 
 int /*<<< orphan*/  DEBUG_TRACE (char*,int,int) ; 
 int aarch64_get_qualifier_standard_value (int const) ; 

__attribute__((used)) static enum aarch64_opnd_qualifier
get_qualifier_from_partial_encoding (aarch64_insn value,
				     const enum aarch64_opnd_qualifier* \
				     candidates,
				     aarch64_insn mask)
{
  int i;
  DEBUG_TRACE ("enter with value: %d, mask: %d", (int)value, (int)mask);
  for (i = 0; i < AARCH64_MAX_QLF_SEQ_NUM; ++i)
    {
      aarch64_insn standard_value;
      if (candidates[i] == AARCH64_OPND_QLF_NIL)
	break;
      standard_value = aarch64_get_qualifier_standard_value (candidates[i]);
      if ((standard_value & mask) == (value & mask))
	return candidates[i];
    }
  return AARCH64_OPND_QLF_NIL;
}