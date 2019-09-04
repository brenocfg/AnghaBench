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
struct bfa_trc_mod_s {int stopped; } ;

/* Variables and functions */

__attribute__((used)) static inline void
bfa_trc_stop(struct bfa_trc_mod_s *trcm)
{
	trcm->stopped = 1;
}