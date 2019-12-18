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
struct TYPE_5__ {TYPE_1__* opts; } ;
typedef  TYPE_2__ TableSpaceCacheEntry ;
struct TYPE_4__ {scalar_t__ effective_io_concurrency; } ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int effective_io_concurrency ; 
 TYPE_2__* get_tablespace (int /*<<< orphan*/ ) ; 

int
get_tablespace_io_concurrency(Oid spcid)
{
	TableSpaceCacheEntry *spc = get_tablespace(spcid);

	if (!spc->opts || spc->opts->effective_io_concurrency < 0)
		return effective_io_concurrency;
	else
		return spc->opts->effective_io_concurrency;
}