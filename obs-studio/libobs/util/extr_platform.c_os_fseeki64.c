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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int _fseeki64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int os_fseeki64(FILE *file, int64_t offset, int origin)
{
#ifdef _MSC_VER
	return _fseeki64(file, offset, origin);
#else
	return fseeko(file, offset, origin);
#endif
}