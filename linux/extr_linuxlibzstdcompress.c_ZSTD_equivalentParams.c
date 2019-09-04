#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hashLog; scalar_t__ chainLog; scalar_t__ strategy; int searchLength; } ;
struct TYPE_6__ {TYPE_1__ cParams; } ;
typedef  TYPE_2__ ZSTD_parameters ;
typedef  int U32 ;

/* Variables and functions */

__attribute__((used)) static U32 ZSTD_equivalentParams(ZSTD_parameters param1, ZSTD_parameters param2)
{
	return (param1.cParams.hashLog == param2.cParams.hashLog) & (param1.cParams.chainLog == param2.cParams.chainLog) &
	       (param1.cParams.strategy == param2.cParams.strategy) & ((param1.cParams.searchLength == 3) == (param2.cParams.searchLength == 3));
}