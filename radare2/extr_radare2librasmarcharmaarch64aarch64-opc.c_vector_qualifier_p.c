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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int AARCH64_OPND_QLF_V_1Q ; 
 int AARCH64_OPND_QLF_V_8B ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline bfd_boolean
vector_qualifier_p (enum aarch64_opnd_qualifier qualifier)
{
  return ((qualifier >= AARCH64_OPND_QLF_V_8B
	  && qualifier <= AARCH64_OPND_QLF_V_1Q) ? TRUE
	  : FALSE);
}