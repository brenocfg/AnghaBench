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
struct rs_rate {int /*<<< orphan*/  index; } ;
struct iwl_lq_sta {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int rs_get_supported_rates (struct iwl_lq_sta*,struct rs_rate*) ; 

__attribute__((used)) static inline bool rs_rate_supported(struct iwl_lq_sta *lq_sta,
				     struct rs_rate *rate)
{
	return BIT(rate->index) & rs_get_supported_rates(lq_sta, rate);
}