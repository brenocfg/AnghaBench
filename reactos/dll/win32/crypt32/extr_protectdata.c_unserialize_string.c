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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CryptMemAlloc (scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  unserialize_dword (int /*<<< orphan*/  const*,scalar_t__*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static
BOOL unserialize_string(const BYTE *ptr, DWORD *index, DWORD size,
                        DWORD len, DWORD width, BOOL inline_len,
                        BYTE ** data, DWORD * stored)
{
    /*TRACE("called\n");*/

    if (!ptr || !data) return FALSE;

    if (inline_len) {
        if (!unserialize_dword(ptr,index,size,&len))
            return FALSE;
    }

    if (*index+len*width>size)
    {
        return FALSE;
    }

    if (!(*data = CryptMemAlloc( len*width)))
    {
        return FALSE;
    }

    memcpy(*data,&(ptr[*index]),len*width);
    if (stored)
    {
        *stored = len;
    }
    *index+=len*width;

    return TRUE;
}