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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 scalar_t__ IMAGEHLP_GetSecurityDirOffset (int /*<<< orphan*/ ,int*,int*) ; 
 int INVALID_SET_FILE_POINTER ; 
 scalar_t__ ReadFile (int /*<<< orphan*/ ,int*,int,int*,int /*<<< orphan*/ *) ; 
 int SetFilePointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL IMAGEHLP_GetCertificateOffset( HANDLE handle, DWORD num,
                                           DWORD *pdwOfs, DWORD *pdwSize )
{
    DWORD size, count, offset, len, sd_VirtualAddr;
    BOOL r;

    r = IMAGEHLP_GetSecurityDirOffset( handle, &sd_VirtualAddr, &size );
    if( !r )
        return FALSE;

    offset = 0;
    /* take the n'th certificate */
    while( 1 )
    {
        /* read the length of the current certificate */
        count = SetFilePointer( handle, sd_VirtualAddr + offset,
                                 NULL, FILE_BEGIN );
        if( count == INVALID_SET_FILE_POINTER )
            return FALSE;
        r = ReadFile( handle, &len, sizeof len, &count, NULL );
        if( !r )
            return FALSE;
        if( count != sizeof len )
            return FALSE;

        /* check the certificate is not too big or too small */
        if( len < sizeof len )
            return FALSE;
        if( len > (size-offset) )
            return FALSE;
        if( !num-- )
            break;

        /* calculate the offset of the next certificate */
        offset += len;

        /* padded out to the nearest 8-byte boundary */
        if( len % 8 )
            offset += 8 - (len % 8);

        if( offset >= size )
            return FALSE;
    }

    *pdwOfs = sd_VirtualAddr + offset;
    *pdwSize = len;

    TRACE("len = %x addr = %x\n", len, sd_VirtualAddr + offset);

    return TRUE;
}