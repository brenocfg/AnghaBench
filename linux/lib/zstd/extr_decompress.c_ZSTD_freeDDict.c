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
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_4__ {struct TYPE_4__* dictBuffer; int /*<<< orphan*/  cMem; } ;
typedef  TYPE_1__ ZSTD_DDict ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/  const) ; 

size_t ZSTD_freeDDict(ZSTD_DDict *ddict)
{
	if (ddict == NULL)
		return 0; /* support free on NULL */
	{
		ZSTD_customMem const cMem = ddict->cMem;
		ZSTD_free(ddict->dictBuffer, cMem);
		ZSTD_free(ddict, cMem);
		return 0;
	}
}