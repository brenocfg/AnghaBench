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
struct cfg80211_internal_bss {int /*<<< orphan*/  hold; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cfg80211_unhold_bss(struct cfg80211_internal_bss *bss)
{
	int r = atomic_dec_return(&bss->hold);
	WARN_ON(r < 0);
}