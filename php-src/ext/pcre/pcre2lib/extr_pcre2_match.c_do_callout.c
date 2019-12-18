#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int capture_top; int* offset_vector; int current_position; size_t callout_number; size_t* callout_string; int callout_string_length; scalar_t__ callout_flags; void* callout_string_offset; void* next_item_length; void* pattern_position; int /*<<< orphan*/  mark; int /*<<< orphan*/  capture_last; } ;
typedef  TYPE_1__ pcre2_callout_block ;
struct TYPE_6__ {int (* callout ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  callout_data; scalar_t__ start_subject; int /*<<< orphan*/  nomatch_mark; TYPE_1__* cb; } ;
typedef  TYPE_2__ match_block ;
typedef  int /*<<< orphan*/  heapframe ;
typedef  int PCRE2_SIZE ;
typedef  scalar_t__ Fovector ;

/* Variables and functions */
 int /*<<< orphan*/  Fcapture_last ; 
 size_t* Fecode ; 
 scalar_t__ Feptr ; 
 scalar_t__ Foffset_top ; 
 void* GET (size_t*,int) ; 
 int LINK_SIZE ; 
 size_t OP_CALLOUT ; 
 int /*<<< orphan*/  OP_lengths ; 
 int PCRE2_UNSET ; 
 void** PRIV (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_callout(heapframe *F, match_block *mb, PCRE2_SIZE *lengthptr)
{
int rc;
PCRE2_SIZE save0, save1;
PCRE2_SIZE *callout_ovector;
pcre2_callout_block *cb;

*lengthptr = (*Fecode == OP_CALLOUT)?
  PRIV(OP_lengths)[OP_CALLOUT] : GET(Fecode, 1 + 2*LINK_SIZE);

if (mb->callout == NULL) return 0;   /* No callout function provided */

/* The original matching code (pre 10.30) worked directly with the ovector
passed by the user, and this was passed to callouts. Now that the working
ovector is in the backtracking frame, it no longer needs to reserve space for
the overall match offsets (which would waste space in the frame). For backward
compatibility, however, we pass capture_top and offset_vector to the callout as
if for the extended ovector, and we ensure that the first two slots are unset
by preserving and restoring their current contents. Picky compilers complain if
references such as Fovector[-2] are use directly, so we set up a separate
pointer. */

callout_ovector = (PCRE2_SIZE *)(Fovector) - 2;

/* The cb->version, cb->subject, cb->subject_length, and cb->start_match fields
are set externally. The first 3 never change; the last is updated for each
bumpalong. */

cb = mb->cb;
cb->capture_top      = (uint32_t)Foffset_top/2 + 1;
cb->capture_last     = Fcapture_last;
cb->offset_vector    = callout_ovector;
cb->mark             = mb->nomatch_mark;
cb->current_position = (PCRE2_SIZE)(Feptr - mb->start_subject);
cb->pattern_position = GET(Fecode, 1);
cb->next_item_length = GET(Fecode, 1 + LINK_SIZE);

if (*Fecode == OP_CALLOUT)  /* Numerical callout */
  {
  cb->callout_number = Fecode[1 + 2*LINK_SIZE];
  cb->callout_string_offset = 0;
  cb->callout_string = NULL;
  cb->callout_string_length = 0;
  }
else  /* String callout */
  {
  cb->callout_number = 0;
  cb->callout_string_offset = GET(Fecode, 1 + 3*LINK_SIZE);
  cb->callout_string = Fecode + (1 + 4*LINK_SIZE) + 1;
  cb->callout_string_length =
    *lengthptr - (1 + 4*LINK_SIZE) - 2;
  }

save0 = callout_ovector[0];
save1 = callout_ovector[1];
callout_ovector[0] = callout_ovector[1] = PCRE2_UNSET;
rc = mb->callout(cb, mb->callout_data);
callout_ovector[0] = save0;
callout_ovector[1] = save1;
cb->callout_flags = 0;
return rc;
}