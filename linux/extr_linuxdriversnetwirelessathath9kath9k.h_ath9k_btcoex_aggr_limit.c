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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 ath9k_btcoex_aggr_limit(struct ath_softc *sc,
					  u32 max_4ms_framelen)
{
	return 0;
}