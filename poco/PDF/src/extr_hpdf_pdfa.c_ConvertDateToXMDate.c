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
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_INVALID_PARAMETER ; 
 scalar_t__ HPDF_OK ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Write (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int strlen (char const*) ; 

HPDF_STATUS ConvertDateToXMDate(HPDF_Stream stream, const char *pDate)
{
    HPDF_STATUS ret;

    if(pDate==NULL) return HPDF_INVALID_PARAMETER;
    if(strlen(pDate)<16) return HPDF_INVALID_PARAMETER;
    if(pDate[0]!='D'||
        pDate[1]!=':') return HPDF_INVALID_PARAMETER;
    pDate+=2;
    /* Copy YYYY */
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)pDate, 4);
    if (ret != HPDF_OK)
        return ret;
    pDate+=4;
    /* Write -MM */
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)"-", 1);
    if (ret != HPDF_OK)
        return ret;
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)pDate, 2);
    if (ret != HPDF_OK)
        return ret;
    pDate+=2;
    /* Write -DD */
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)"-", 1);
    if (ret != HPDF_OK)
        return ret;
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)pDate, 2);
    if (ret != HPDF_OK)
        return ret;
    pDate+=2;
    /* Write THH */
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)"T", 1);
    if (ret != HPDF_OK)
        return ret;
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)pDate, 2);
    if (ret != HPDF_OK)
        return ret;
    pDate+=2;
    /* Write :mm */
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)":", 1);
    if (ret != HPDF_OK)
        return ret;
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)pDate, 2);
    if (ret != HPDF_OK)
        return ret;
    pDate+=2;
    /* Write :SS */
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)":", 1);
    if (ret != HPDF_OK)
        return ret;
    ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)pDate, 2);
    if (ret != HPDF_OK)
        return ret;
    pDate+=2;
    /* Write +... */
    if(pDate[0]==0) {
        ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)"Z", 1);
        return ret;
    }
    if(pDate[0]=='+'||pDate[0]=='-') {
        ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)pDate, 3);
        if (ret != HPDF_OK)
            return ret;
        pDate+=4;
        ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)":", 1);
        if (ret != HPDF_OK)
            return ret;
        ret = HPDF_Stream_Write(stream, (const HPDF_BYTE*)pDate, 2);
        if (ret != HPDF_OK)
            return ret;
        return ret;
    }
    return HPDF_SetError (stream->error, HPDF_INVALID_PARAMETER, 0);
}