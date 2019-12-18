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
 int fseeko64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fseek_x(FILE *fp, int64_t offset, int origin)
{
#if defined(WIN32) && defined(__GNUC__)
    return fseeko64(fp, offset, origin);
#elif defined(WIN32) && defined(_MSC_VER)
    return _fseeki64(fp, offset, origin);
#else
    return fseeko(fp, offset, origin);
#endif
}