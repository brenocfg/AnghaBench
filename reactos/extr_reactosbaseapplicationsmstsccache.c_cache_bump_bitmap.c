#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
typedef  size_t uint16 ;
struct TYPE_2__ {int next; int previous; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int /*<<< orphan*/  IS_PERSISTENT (size_t) ; 
 scalar_t__ IS_SET (int) ; 
 int NOT_SET ; 
 TYPE_1__** g_bmpcache ; 
 int /*<<< orphan*/ * g_bmpcache_count ; 
 int* g_bmpcache_lru ; 
 size_t* g_bmpcache_mru ; 

void
cache_bump_bitmap(uint8 id, uint16 idx, int bump)
{
	int p_idx, n_idx, n;

	if (!IS_PERSISTENT(id))
		return;

	if (g_bmpcache_mru[id] == idx)
		return;

	DEBUG_RDP5(("bump bitmap: id=%d, idx=%d, bump=%d\n", id, idx, bump));

	n_idx = g_bmpcache[id][idx].next;
	p_idx = g_bmpcache[id][idx].previous;

	if (IS_SET(n_idx))
	{
		/* remove */
		--g_bmpcache_count[id];
		if (IS_SET(p_idx))
			g_bmpcache[id][p_idx].next = n_idx;
		else
			g_bmpcache_lru[id] = n_idx;
		if (IS_SET(n_idx))
			g_bmpcache[id][n_idx].previous = p_idx;
		else
			g_bmpcache_mru[id] = p_idx;
	}
	else
	{
		p_idx = NOT_SET;
		n_idx = g_bmpcache_lru[id];
	}

	if (bump >= 0)
	{
		for (n = 0; n < bump && IS_SET(n_idx); n++)
		{
			p_idx = n_idx;
			n_idx = g_bmpcache[id][p_idx].next;
		}
	}
	else
	{
		p_idx = g_bmpcache_mru[id];
		n_idx = NOT_SET;
	}

	/* insert */
	++g_bmpcache_count[id];
	g_bmpcache[id][idx].previous = p_idx;
	g_bmpcache[id][idx].next = n_idx;

	if (p_idx >= 0)
		g_bmpcache[id][p_idx].next = idx;
	else
		g_bmpcache_lru[id] = idx;

	if (n_idx >= 0)
		g_bmpcache[id][n_idx].previous = idx;
	else
		g_bmpcache_mru[id] = idx;
}