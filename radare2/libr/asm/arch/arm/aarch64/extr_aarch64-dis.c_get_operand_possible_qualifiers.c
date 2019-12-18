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
typedef  int* aarch64_opnd_qualifier_seq_t ;

/* Variables and functions */
 int AARCH64_MAX_QLF_SEQ_NUM ; 
 int AARCH64_OPND_QLF_NIL ; 

__attribute__((used)) static void
get_operand_possible_qualifiers (int idx,
				 const aarch64_opnd_qualifier_seq_t *list,
				 enum aarch64_opnd_qualifier *qualifiers)
{
  int i;
  for (i = 0; i < AARCH64_MAX_QLF_SEQ_NUM; ++i)
    if ((qualifiers[i] = list[i][idx]) == AARCH64_OPND_QLF_NIL)
      break;
}