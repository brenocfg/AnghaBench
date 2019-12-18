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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int* LPWSTR ;
typedef  int* LPCWSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int MAX_STREAM_NAME ; 
 int /*<<< orphan*/  debugstr_w (int*) ; 
 int lstrlenW (int*) ; 
 int* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int*) ; 
 int utf2mime (int) ; 

LPWSTR encode_streamname(BOOL bTable, LPCWSTR in)
{
    DWORD count = MAX_STREAM_NAME;
    DWORD ch, next;
    LPWSTR out, p;

    if( !bTable )
        count = lstrlenW( in )+2;
    if (!(out = msi_alloc( count*sizeof(WCHAR) ))) return NULL;
    p = out;

    if( bTable )
    {
         *p++ = 0x4840;
         count --;
    }
    while( count -- ) 
    {
        ch = *in++;
        if( !ch )
        {
            *p = ch;
            return out;
        }
        if( ( ch < 0x80 ) && ( utf2mime(ch) >= 0 ) )
        {
            ch = utf2mime(ch) + 0x4800;
            next = *in;
            if( next && (next<0x80) )
            {
                next = utf2mime(next);
                if( next != -1 )
                {
                     next += 0x3ffffc0;
                     ch += (next<<6);
                     in++;
                }
            }
        }
        *p++ = ch;
    }
    ERR("Failed to encode stream name (%s)\n",debugstr_w(in));
    msi_free( out );
    return NULL;
}