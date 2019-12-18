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
typedef  int WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  is_sepW (int const) ; 
 int strlenW (int const*) ; 
 int /*<<< orphan*/  strncpyW (int*,int const*,int) ; 

__attribute__((used)) static inline void file_pathW(const WCHAR* srcFileNameW,
    WCHAR* dstFilePathW)
{
    int len;

    for (len = strlenW(srcFileNameW) - 1; (len > 0) && (!is_sepW(srcFileNameW[len])); len--);

    strncpyW(dstFilePathW, srcFileNameW, len);
    dstFilePathW[len] = L'\0';
}