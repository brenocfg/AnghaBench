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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  HPDF_UINT16 ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_OK ; 
 scalar_t__ HPDF_Stream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UINT16Swap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HPDF_STATUS
WriteUINT16 (HPDF_Stream   stream,
             HPDF_UINT16   value)
{
    HPDF_STATUS ret;
    HPDF_UINT16 tmp = value;

    UINT16Swap (&tmp);

    ret = HPDF_Stream_Write (stream, (HPDF_BYTE *)&tmp, sizeof(tmp));
    if (ret != HPDF_OK)
        return ret;

    return HPDF_OK;
}