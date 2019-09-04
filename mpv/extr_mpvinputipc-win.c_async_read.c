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
typedef  int /*<<< orphan*/  OVERLAPPED ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ ReadFile (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD async_read(HANDLE file, void *buf, unsigned size, OVERLAPPED* ol)
{
    DWORD err = ReadFile(file, buf, size, NULL, ol) ? 0 : GetLastError();
    return err == ERROR_IO_PENDING ? 0 : err;
}