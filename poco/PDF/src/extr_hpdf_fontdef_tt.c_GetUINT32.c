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
typedef  scalar_t__ HPDF_UINT32 ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_OK ; 
 scalar_t__ HPDF_Stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  UINT32Swap (scalar_t__*) ; 

__attribute__((used)) static HPDF_STATUS
GetUINT32 (HPDF_Stream         stream,
           HPDF_UINT32         *value)
{
    HPDF_STATUS ret;
    HPDF_UINT size = sizeof (HPDF_UINT32);

    ret = HPDF_Stream_Read (stream, (HPDF_BYTE *)value, &size);
    if (ret != HPDF_OK) {
        *value = 0;
        return ret;
    }

    UINT32Swap (value);

    return HPDF_OK;
}