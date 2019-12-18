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
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 

errno_t fopen_s(FILE **pFile, const char *filename, const char *mode)
{
    if (pFile == NULL || filename == NULL || mode == NULL)
        return EINVAL;
    *pFile = fopen(filename, mode);
    if (*pFile != NULL)
        return 0;
    else
        return errno;
}