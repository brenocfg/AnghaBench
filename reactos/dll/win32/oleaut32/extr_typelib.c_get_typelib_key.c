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
typedef  int /*<<< orphan*/  WORD ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  TypelibW ;
typedef  int /*<<< orphan*/  REFGUID ;

/* Variables and functions */
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlenW (char*) ; 

__attribute__((used)) static WCHAR *get_typelib_key( REFGUID guid, WORD wMaj, WORD wMin, WCHAR *buffer )
{
    static const WCHAR TypelibW[] = {'T','y','p','e','l','i','b','\\',0};
    static const WCHAR VersionFormatW[] = {'\\','%','x','.','%','x',0};

    memcpy( buffer, TypelibW, sizeof(TypelibW) );
    StringFromGUID2( guid, buffer + strlenW(buffer), 40 );
    sprintfW( buffer + strlenW(buffer), VersionFormatW, wMaj, wMin );
    return buffer;
}