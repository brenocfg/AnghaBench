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
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/ * CreateFileW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 

__attribute__((used)) static HANDLE
OpenRdpFile(LPWSTR path, BOOL bWrite)
{
    HANDLE hFile = NULL;

    if (path)
    {
        hFile = CreateFileW(path,
                            bWrite ? GENERIC_WRITE : GENERIC_READ,
                            0,
                            NULL,
                            bWrite ? CREATE_ALWAYS : OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_HIDDEN,
                            NULL);
    }

    return hFile;
}