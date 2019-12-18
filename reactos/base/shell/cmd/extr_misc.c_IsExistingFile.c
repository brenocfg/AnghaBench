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
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GetFileAttributes (int /*<<< orphan*/ ) ; 

BOOL IsExistingFile (LPCTSTR pszPath)
{
    DWORD attr = GetFileAttributes (pszPath);
    return (attr != 0xFFFFFFFF && (! (attr & FILE_ATTRIBUTE_DIRECTORY)) );
}