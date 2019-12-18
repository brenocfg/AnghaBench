#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ enableLdm; scalar_t__ hashLog; scalar_t__ bucketSizeLog; scalar_t__ minMatchLength; scalar_t__ hashEveryLog; } ;
typedef  TYPE_1__ ldmParams_t ;
typedef  int U32 ;

/* Variables and functions */

__attribute__((used)) static U32 ZSTD_equivalentLdmParams(ldmParams_t ldmParams1,
                                    ldmParams_t ldmParams2)
{
    return (!ldmParams1.enableLdm && !ldmParams2.enableLdm) ||
           (ldmParams1.enableLdm == ldmParams2.enableLdm &&
            ldmParams1.hashLog == ldmParams2.hashLog &&
            ldmParams1.bucketSizeLog == ldmParams2.bucketSizeLog &&
            ldmParams1.minMatchLength == ldmParams2.minMatchLength &&
            ldmParams1.hashEveryLog == ldmParams2.hashEveryLog);
}