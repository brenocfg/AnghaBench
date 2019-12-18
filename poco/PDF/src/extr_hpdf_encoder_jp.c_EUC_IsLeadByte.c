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
typedef  int /*<<< orphan*/  HPDF_Encoder ;
typedef  int HPDF_BYTE ;
typedef  int HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_BOOL
EUC_IsLeadByte  (HPDF_Encoder    encoder,
                 HPDF_BYTE       b)
{
    HPDF_UNUSED (encoder);
    return ((b >= 0xa1 && b <= 0xfe) || b == 0x8e);
}