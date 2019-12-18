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
typedef  int /*<<< orphan*/  partitionW ;
typedef  char WCHAR ;

/* Variables and functions */
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static WCHAR *get_osname( const WCHAR *caption )
{
    static const WCHAR partitionW[] =
        {'|','C',':','\\','W','I','N','D','O','W','S','|','\\','D','e','v','i','c','e','\\',
         'H','a','r','d','d','i','s','k','0','\\','P','a','r','t','i','t','i','o','n','1',0};
    int len = strlenW( caption );
    WCHAR *ret;

    if (!(ret = heap_alloc( len * sizeof(WCHAR) + sizeof(partitionW) ))) return NULL;
    memcpy( ret, caption, len * sizeof(WCHAR) );
    memcpy( ret + len, partitionW, sizeof(partitionW) );
    return ret;
}