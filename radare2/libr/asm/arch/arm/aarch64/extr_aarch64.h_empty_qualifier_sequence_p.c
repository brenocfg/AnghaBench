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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  scalar_t__ aarch64_opnd_qualifier_t ;

/* Variables and functions */
 int AARCH64_MAX_OPND_NUM ; 
 scalar_t__ const AARCH64_OPND_QLF_NIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline bfd_boolean
empty_qualifier_sequence_p (const aarch64_opnd_qualifier_t *qualifiers)
{
  int i;
  for (i = 0; i < AARCH64_MAX_OPND_NUM; ++i)
    if (qualifiers[i] != AARCH64_OPND_QLF_NIL)
      return FALSE;
  return TRUE;
}