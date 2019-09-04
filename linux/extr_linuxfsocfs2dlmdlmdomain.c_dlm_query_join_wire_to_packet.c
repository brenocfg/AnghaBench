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
struct dlm_query_join_packet {int dummy; } ;
union dlm_query_join_response {struct dlm_query_join_packet packet; int /*<<< orphan*/  intval; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_query_join_wire_to_packet(u32 wire,
					  struct dlm_query_join_packet *packet)
{
	union dlm_query_join_response response;

	response.intval = cpu_to_be32(wire);
	*packet = response.packet;
}