#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ (* is_lead_byte_fn ) (TYPE_2__*,int /*<<< orphan*/ ) ;scalar_t__ (* is_trial_byte_fn ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {size_t index; size_t len; scalar_t__ byte_type; int /*<<< orphan*/ * text; } ;
typedef  TYPE_1__ HPDF_ParseText_Rec ;
typedef  TYPE_2__* HPDF_Encoder ;
typedef  TYPE_3__* HPDF_CMapEncoderAttr ;
typedef  scalar_t__ HPDF_ByteType ;

/* Variables and functions */
 scalar_t__ HPDF_BYTE_TYPE_LEAD ; 
 scalar_t__ HPDF_BYTE_TYPE_SINGLE ; 
 scalar_t__ HPDF_BYTE_TYPE_TRIAL ; 
 scalar_t__ HPDF_BYTE_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 

HPDF_ByteType
HPDF_CMapEncoder_ByteType  (HPDF_Encoder        encoder,
                            HPDF_ParseText_Rec  *state)
{
    HPDF_CMapEncoderAttr attr = (HPDF_CMapEncoderAttr)encoder->attr;

    HPDF_PTRACE ((" HPDF_CMapEncoder_ByteType\n"));

    if (state->index >= state->len)
        return HPDF_BYTE_TYPE_UNKNOWN;

    if (state->byte_type == HPDF_BYTE_TYPE_LEAD) {
        if (attr->is_trial_byte_fn (encoder, state->text[state->index]))
            state->byte_type = HPDF_BYTE_TYPE_TRIAL;
        else
            state->byte_type = HPDF_BYTE_TYPE_UNKNOWN;
   } else {
        if (attr->is_lead_byte_fn (encoder, state->text[state->index]))
            state->byte_type = HPDF_BYTE_TYPE_LEAD;
        else
            state->byte_type = HPDF_BYTE_TYPE_SINGLE;
   }

   state->index++;

   return state->byte_type;
}