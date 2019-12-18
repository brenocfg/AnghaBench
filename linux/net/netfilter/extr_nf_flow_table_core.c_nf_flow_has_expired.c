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
struct flow_offload {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 scalar_t__ nf_flow_timeout_delta (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool nf_flow_has_expired(const struct flow_offload *flow)
{
	return nf_flow_timeout_delta(flow->timeout) <= 0;
}