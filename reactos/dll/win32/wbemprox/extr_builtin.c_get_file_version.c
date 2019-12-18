#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_2__ {int dwFileVersionMS; int dwFileVersionLS; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int GetFileVersionInfoSizeW (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFileVersionInfoW (char const*,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  VerQueryValueW (void*,char const*,void**,int*) ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (void*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int,int,int,int) ; 

__attribute__((used)) static WCHAR *get_file_version( const WCHAR *filename )
{
    static const WCHAR slashW[] = {'\\',0}, fmtW[] = {'%','u','.','%','u','.','%','u','.','%','u',0};
    VS_FIXEDFILEINFO *info;
    DWORD size;
    void *block;
    WCHAR *ret;

    if (!(ret = heap_alloc( (4 * 5 + ARRAY_SIZE( fmtW )) * sizeof(WCHAR) ))) return NULL;
    if (!(size = GetFileVersionInfoSizeW( filename, NULL )) || !(block = heap_alloc( size )))
    {
        heap_free( ret );
        return NULL;
    }
    if (!GetFileVersionInfoW( filename, 0, size, block ) ||
        !VerQueryValueW( block, slashW, (void **)&info, &size ))
    {
        heap_free( block );
        heap_free( ret );
        return NULL;
    }
    sprintfW( ret, fmtW, info->dwFileVersionMS >> 16, info->dwFileVersionMS & 0xffff,
                         info->dwFileVersionLS >> 16, info->dwFileVersionLS & 0xffff );
    heap_free( block );
    return ret;
}