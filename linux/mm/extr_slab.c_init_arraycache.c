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
struct array_cache {int limit; int batchcount; scalar_t__ touched; scalar_t__ avail; } ;

/* Variables and functions */

__attribute__((used)) static void init_arraycache(struct array_cache *ac, int limit, int batch)
{
	if (ac) {
		ac->avail = 0;
		ac->limit = limit;
		ac->batchcount = batch;
		ac->touched = 0;
	}
}