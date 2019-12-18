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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int nLen; int nBuffer; int /*<<< orphan*/ * szData; } ;
typedef  TYPE_1__ ME_String ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int ME_GetOptimalBuffer (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * heap_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

BOOL ME_InsertString(ME_String *s, int ofs, const WCHAR *insert, int len)
{
    DWORD new_len = s->nLen + len + 1;
    WCHAR *new;

    assert( s->nBuffer ); /* Not a const string */
    assert( ofs <= s->nLen );

    if( new_len > s->nBuffer )
    {
        s->nBuffer = ME_GetOptimalBuffer( new_len );
        new = heap_realloc( s->szData, s->nBuffer * sizeof(WCHAR) );
        if (!new) return FALSE;
        s->szData = new;
    }

    memmove( s->szData + ofs + len, s->szData + ofs, (s->nLen - ofs + 1) * sizeof(WCHAR) );
    memcpy( s->szData + ofs, insert, len * sizeof(WCHAR) );
    s->nLen += len;

    return TRUE;
}