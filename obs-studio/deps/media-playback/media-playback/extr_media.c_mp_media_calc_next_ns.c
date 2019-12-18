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
struct TYPE_4__ {int next_pts_ns; int next_ns; } ;
typedef  TYPE_1__ mp_media_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int mp_media_get_next_min_pts (TYPE_1__*) ; 

__attribute__((used)) static void mp_media_calc_next_ns(mp_media_t *m)
{
	int64_t min_next_ns = mp_media_get_next_min_pts(m);

	int64_t delta = min_next_ns - m->next_pts_ns;
#ifdef _DEBUG
	assert(delta >= 0);
#endif
	if (delta < 0)
		delta = 0;
	if (delta > 3000000000)
		delta = 0;

	m->next_ns += delta;
	m->next_pts_ns = min_next_ns;
}