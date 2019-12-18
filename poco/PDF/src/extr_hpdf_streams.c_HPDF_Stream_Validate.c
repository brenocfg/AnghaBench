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
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FALSE ; 
 scalar_t__ HPDF_STREAM_SIG_BYTES ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_STATUS
HPDF_Stream_Validate  (HPDF_Stream  stream)
{
    if (!stream || stream->sig_bytes != HPDF_STREAM_SIG_BYTES)
        return HPDF_FALSE;
    else
        return HPDF_TRUE;
}