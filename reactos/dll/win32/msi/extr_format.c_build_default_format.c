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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int DWORD ;

/* Variables and functions */
 int MSI_RecordGetFieldCount (int /*<<< orphan*/  const*) ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 char* msi_realloc (char*,int) ; 
 scalar_t__ sprintfW (char*,char const*,int,int) ; 
 int /*<<< orphan*/  strcatW (char*,char*) ; 

__attribute__((used)) static WCHAR *build_default_format( const MSIRECORD *record )
{
    static const WCHAR fmt[] = {'%','i',':',' ','[','%','i',']',' ',0};
    int i, count = MSI_RecordGetFieldCount( record );
    WCHAR *ret, *tmp, buf[26];
    DWORD size = 1;

    if (!(ret = msi_alloc( sizeof(*ret) ))) return NULL;
    ret[0] = 0;

    for (i = 1; i <= count; i++)
    {
        size += sprintfW( buf, fmt, i, i );
        if (!(tmp = msi_realloc( ret, size * sizeof(*ret) )))
        {
            msi_free( ret );
            return NULL;
        }
        ret = tmp;
        strcatW( ret, buf );
    }
    return ret;
}