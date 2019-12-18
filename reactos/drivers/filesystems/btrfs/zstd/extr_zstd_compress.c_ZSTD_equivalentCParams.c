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
struct TYPE_4__ {scalar_t__ hashLog; scalar_t__ chainLog; scalar_t__ strategy; int searchLength; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;
typedef  int U32 ;

/* Variables and functions */

__attribute__((used)) static U32 ZSTD_equivalentCParams(ZSTD_compressionParameters cParams1,
                                  ZSTD_compressionParameters cParams2)
{
    return (cParams1.hashLog  == cParams2.hashLog)
         & (cParams1.chainLog == cParams2.chainLog)
         & (cParams1.strategy == cParams2.strategy)   /* opt parser space */
         & ((cParams1.searchLength==3) == (cParams2.searchLength==3));  /* hashlog3 space */
}