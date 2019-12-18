#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ next_ns; } ;
typedef  TYPE_1__ mp_media_t ;

/* Variables and functions */
 scalar_t__ os_gettime_ns () ; 
 int /*<<< orphan*/  os_sleepto_ns (scalar_t__) ; 

__attribute__((used)) static inline bool mp_media_sleepto(mp_media_t *m)
{
	bool timeout = false;

	if (!m->next_ns) {
		m->next_ns = os_gettime_ns();
	} else {
		uint64_t t = os_gettime_ns();
		const uint64_t timeout_ns = 200000000;

		if (m->next_ns > t && (m->next_ns - t) > timeout_ns) {
			os_sleepto_ns(t + timeout_ns);
			timeout = true;
		} else {
			os_sleepto_ns(m->next_ns);
		}
	}

	return timeout;
}