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
struct rs_rate {int /*<<< orphan*/  stbc; int /*<<< orphan*/  ldpc; int /*<<< orphan*/  sgi; int /*<<< orphan*/  bw; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_pretty_rate (struct rs_rate const*) ; 

__attribute__((used)) static inline void rs_dump_rate(struct iwl_mvm *mvm, const struct rs_rate *rate,
				const char *prefix)
{
	IWL_DEBUG_RATE(mvm,
		       "%s: %s BW: %d SGI: %d LDPC: %d STBC: %d\n",
		       prefix, rs_pretty_rate(rate), rate->bw,
		       rate->sgi, rate->ldpc, rate->stbc);
}