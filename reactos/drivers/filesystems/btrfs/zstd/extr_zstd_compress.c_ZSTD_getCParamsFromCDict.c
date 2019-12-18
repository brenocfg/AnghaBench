#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
struct TYPE_4__ {int /*<<< orphan*/  cParams; } ;
struct TYPE_5__ {TYPE_1__ matchState; } ;
typedef  TYPE_2__ ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

ZSTD_compressionParameters ZSTD_getCParamsFromCDict(const ZSTD_CDict* cdict)
{
    assert(cdict != NULL);
    return cdict->matchState.cParams;
}