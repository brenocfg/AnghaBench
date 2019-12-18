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
struct chmLzxcControlData {int size; int version; int resetInterval; int windowSize; int windowsPerReset; int unknown_18; int /*<<< orphan*/  signature; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int _CHM_LZXC_MIN_LEN ; 
 unsigned int _CHM_LZXC_V2_LEN ; 
 int /*<<< orphan*/  _unmarshal_char_array (unsigned char**,unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _unmarshal_uint32 (unsigned char**,unsigned int*,int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static BOOL _unmarshal_lzxc_control_data(unsigned char **pData,
                                         unsigned int *pDataLen,
                                         struct chmLzxcControlData *dest)
{
    /* we want at least 0x18 bytes */
    if (*pDataLen < _CHM_LZXC_MIN_LEN)
        return FALSE;

    /* unmarshal fields */
    _unmarshal_uint32    (pData, pDataLen, &dest->size);
    _unmarshal_char_array(pData, pDataLen,  dest->signature, 4);
    _unmarshal_uint32    (pData, pDataLen, &dest->version);
    _unmarshal_uint32    (pData, pDataLen, &dest->resetInterval);
    _unmarshal_uint32    (pData, pDataLen, &dest->windowSize);
    _unmarshal_uint32    (pData, pDataLen, &dest->windowsPerReset);

    if (*pDataLen >= _CHM_LZXC_V2_LEN)
        _unmarshal_uint32    (pData, pDataLen, &dest->unknown_18);
    else
        dest->unknown_18 = 0;

    if (dest->version == 2)
    {
        dest->resetInterval *= 0x8000;
        dest->windowSize *= 0x8000;
    }
    if (dest->windowSize == 0  ||  dest->resetInterval == 0)
        return FALSE;

    /* for now, only support resetInterval a multiple of windowSize/2 */
    if (dest->windowSize == 1)
        return FALSE;
    if ((dest->resetInterval % (dest->windowSize/2)) != 0)
        return FALSE;

    /* check structure */
    if (memcmp(dest->signature, "LZXC", 4) != 0)
        return FALSE;

    return TRUE;
}