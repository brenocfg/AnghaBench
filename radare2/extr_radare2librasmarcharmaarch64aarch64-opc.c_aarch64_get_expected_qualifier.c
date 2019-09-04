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
typedef  scalar_t__ aarch64_opnd_qualifier_t ;
typedef  scalar_t__ const* aarch64_opnd_qualifier_seq_t ;

/* Variables and functions */
 int AARCH64_MAX_QLF_SEQ_NUM ; 
 scalar_t__ const AARCH64_OPND_NIL ; 
 int /*<<< orphan*/  assert (int) ; 

aarch64_opnd_qualifier_t
aarch64_get_expected_qualifier (const aarch64_opnd_qualifier_seq_t *qseq_list,
				int idx,
				const aarch64_opnd_qualifier_t known_qlf,
				int known_idx)
{
  int i, saved_i;

  /* Special case.

     When the known qualifier is NIL, we have to assume that there is only
     one qualifier sequence in the *QSEQ_LIST and return the corresponding
     qualifier directly.  One scenario is that for instruction
	PRFM <prfop>, [<Xn|SP>, #:lo12:<symbol>]
     which has only one possible valid qualifier sequence
	NIL, S_D
     the caller may pass NIL in KNOWN_QLF to obtain S_D so that it can
     determine the correct relocation type (i.e. LDST64_LO12) for PRFM.

     Because the qualifier NIL has dual roles in the qualifier sequence:
     it can mean no qualifier for the operand, or the qualifer sequence is
     not in use (when all qualifiers in the sequence are NILs), we have to
     handle this special case here.  */
  if (known_qlf == AARCH64_OPND_NIL)
    {
      assert (qseq_list[0][known_idx] == AARCH64_OPND_NIL);
      return qseq_list[0][idx];
    }

  for (i = 0, saved_i = -1; i < AARCH64_MAX_QLF_SEQ_NUM; ++i)
    {
      if (qseq_list[i][known_idx] == known_qlf)
	{
	  if (saved_i != -1)
	    /* More than one sequences are found to have KNOWN_QLF at
	       KNOWN_IDX.  */
	    return AARCH64_OPND_NIL;
	  saved_i = i;
	}
    }

  return qseq_list[saved_i][idx];
}