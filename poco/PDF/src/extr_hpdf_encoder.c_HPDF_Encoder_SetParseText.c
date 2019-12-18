#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  byte_type; int /*<<< orphan*/  len; scalar_t__ index; int /*<<< orphan*/  const* text; } ;
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  TYPE_1__ HPDF_ParseText_Rec ;
typedef  int /*<<< orphan*/  HPDF_Encoder ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_BYTE_TYPE_SINGLE ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_UNUSED (int /*<<< orphan*/ ) ; 

void
HPDF_Encoder_SetParseText  (HPDF_Encoder        encoder,
                            HPDF_ParseText_Rec  *state,
                            const HPDF_BYTE     *text,
                            HPDF_UINT           len)
{
    HPDF_PTRACE ((" HPDF_CMapEncoder_SetParseText\n"));
    HPDF_UNUSED (encoder);

    state->text = text;
    state->index = 0;
    state->len = len;
    state->byte_type = HPDF_BYTE_TYPE_SINGLE;
}