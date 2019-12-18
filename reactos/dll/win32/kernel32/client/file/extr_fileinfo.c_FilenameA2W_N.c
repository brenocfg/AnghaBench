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
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  RtlMultiByteToUnicodeN (scalar_t__*,int,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlOemToUnicodeN (scalar_t__*,int,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bIsFileApiAnsi ; 
 int strlen (scalar_t__) ; 

DWORD
FilenameA2W_N(
   LPWSTR dest,
   INT destlen, /* buffer size in TCHARS incl. nullchar */
   LPCSTR src,
   INT srclen /* buffer size in TCHARS incl. nullchar */
   )
{
    DWORD ret;

    if (srclen < 0) srclen = strlen( src ) + 1;

    if (bIsFileApiAnsi)
        RtlMultiByteToUnicodeN( dest, destlen* sizeof(WCHAR), &ret, (LPSTR)src, srclen  );
    else
        RtlOemToUnicodeN( dest, destlen* sizeof(WCHAR), &ret, (LPSTR)src, srclen );

    if (ret) dest[(ret/sizeof(WCHAR))-1]=0;

    return ret/sizeof(WCHAR);
}