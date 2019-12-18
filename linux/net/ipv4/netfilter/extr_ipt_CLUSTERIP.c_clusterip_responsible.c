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
typedef  scalar_t__ u_int32_t ;
struct clusterip_config {int /*<<< orphan*/  local_nodes; } ;

/* Variables and functions */
 int test_bit (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
clusterip_responsible(const struct clusterip_config *config, u_int32_t hash)
{
	return test_bit(hash - 1, &config->local_nodes);
}