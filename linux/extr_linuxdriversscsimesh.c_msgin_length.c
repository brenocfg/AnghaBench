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
struct mesh_state {int n_msgin; int* msgin; } ;

/* Variables and functions */

__attribute__((used)) static inline int msgin_length(struct mesh_state *ms)
{
	int b, n;

	n = 1;
	if (ms->n_msgin > 0) {
		b = ms->msgin[0];
		if (b == 1) {
			/* extended message */
			n = ms->n_msgin < 2? 2: ms->msgin[1] + 2;
		} else if (0x20 <= b && b <= 0x2f) {
			/* 2-byte message */
			n = 2;
		}
	}
	return n;
}