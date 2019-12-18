#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* byte_type_fn ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  HPDF_ParseText_Rec ;
typedef  TYPE_1__* HPDF_Encoder ;
typedef  int /*<<< orphan*/  HPDF_ByteType ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_BYTE_TYPE_SINGLE ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

HPDF_ByteType
HPDF_Encoder_ByteType  (HPDF_Encoder        encoder,
                        HPDF_ParseText_Rec  *state)
{
    HPDF_PTRACE ((" HPDF_Encoder_ByteType\n"));

    if (encoder->byte_type_fn)
        return encoder->byte_type_fn (encoder, state);
    else
        return HPDF_BYTE_TYPE_SINGLE;
}