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
typedef  int /*<<< orphan*/  HUF_CElt ;

/* Variables and functions */
 size_t HUF_compress1X_usingCTable_internal_bmi2 (void*,size_t,void const*,size_t,int /*<<< orphan*/  const*) ; 
 size_t HUF_compress1X_usingCTable_internal_default (void*,size_t,void const*,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static size_t
HUF_compress1X_usingCTable_internal(void* dst, size_t dstSize,
                              const void* src, size_t srcSize,
                              const HUF_CElt* CTable, const int bmi2)
{
    if (bmi2) {
        return HUF_compress1X_usingCTable_internal_bmi2(dst, dstSize, src, srcSize, CTable);
    }
    return HUF_compress1X_usingCTable_internal_default(dst, dstSize, src, srcSize, CTable);
}