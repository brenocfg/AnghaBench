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
typedef  enum data_pattern { ____Placeholder_data_pattern } data_pattern ;
typedef  scalar_t__* aarch64_opnd_qualifier_seq_t ;

/* Variables and functions */
 scalar_t__ AARCH64_OPND_QLF_NIL ; 
 int DP_UNKNOWN ; 
 int DP_VECTOR_3SAME ; 
 int DP_VECTOR_ACROSS_LANES ; 
 int DP_VECTOR_LONG ; 
 int DP_VECTOR_WIDE ; 
 scalar_t__ TRUE ; 
 scalar_t__ aarch64_get_qualifier_esize (scalar_t__) ; 
 scalar_t__ fp_qualifier_p (scalar_t__) ; 
 scalar_t__ vector_qualifier_p (scalar_t__) ; 

__attribute__((used)) static enum data_pattern
get_data_pattern (const aarch64_opnd_qualifier_seq_t qualifiers)
{
  if (vector_qualifier_p (qualifiers[0]) == TRUE)
    {
      /* e.g. v.4s, v.4s, v.4s
	   or v.4h, v.4h, v.h[3].  */
      if (qualifiers[0] == qualifiers[1]
	  && vector_qualifier_p (qualifiers[2]) == TRUE
	  && (aarch64_get_qualifier_esize (qualifiers[0])
	      == aarch64_get_qualifier_esize (qualifiers[1]))
	  && (aarch64_get_qualifier_esize (qualifiers[0])
	      == aarch64_get_qualifier_esize (qualifiers[2])))
	return DP_VECTOR_3SAME;
      /* e.g. v.8h, v.8b, v.8b.
           or v.4s, v.4h, v.h[2].
	   or v.8h, v.16b.  */
      if (vector_qualifier_p (qualifiers[1]) == TRUE
	  && aarch64_get_qualifier_esize (qualifiers[0]) != 0
	  && (aarch64_get_qualifier_esize (qualifiers[0])
	      == aarch64_get_qualifier_esize (qualifiers[1]) << 1))
	return DP_VECTOR_LONG;
      /* e.g. v.8h, v.8h, v.8b.  */
      if (qualifiers[0] == qualifiers[1]
	  && vector_qualifier_p (qualifiers[2]) == TRUE
	  && aarch64_get_qualifier_esize (qualifiers[0]) != 0
	  && (aarch64_get_qualifier_esize (qualifiers[0])
	      == aarch64_get_qualifier_esize (qualifiers[2]) << 1)
	  && (aarch64_get_qualifier_esize (qualifiers[0])
	      == aarch64_get_qualifier_esize (qualifiers[1])))
	return DP_VECTOR_WIDE;
    }
  else if (fp_qualifier_p (qualifiers[0]) == TRUE)
    {
      /* e.g. SADDLV <V><d>, <Vn>.<T>.  */
      if (vector_qualifier_p (qualifiers[1]) == TRUE
	  && qualifiers[2] == AARCH64_OPND_QLF_NIL)
	return DP_VECTOR_ACROSS_LANES;
    }

  return DP_UNKNOWN;
}