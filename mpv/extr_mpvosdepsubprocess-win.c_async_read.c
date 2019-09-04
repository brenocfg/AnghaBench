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

/* Variables and functions */
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int async_read(HANDLE file, void *buf, unsigned size, OVERLAPPED* ol)
{
    if (!ReadFile(file, buf, size, NULL, ol))
        return (GetLastError() == ERROR_IO_PENDING) ? 0 : -1;
    return 0;
}