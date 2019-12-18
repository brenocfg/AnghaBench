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
struct TYPE_3__ {scalar_t__ sig_bytes; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Encoder ;

/* Variables and functions */
 scalar_t__ HPDF_ENCODER_SIG_BYTES ; 
 int /*<<< orphan*/  HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_STATUS
HPDF_Encoder_Validate  (HPDF_Encoder  encoder)
{
    HPDF_PTRACE ((" HPDF_Encoder_Validate\n"));

    if (!encoder || encoder->sig_bytes != HPDF_ENCODER_SIG_BYTES)
        return HPDF_FALSE;
    else
        return HPDF_TRUE;
}