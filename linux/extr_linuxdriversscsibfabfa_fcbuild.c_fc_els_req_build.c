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
typedef  void* u32 ;
struct fchs_s {int /*<<< orphan*/  ox_id; void* s_id; void* d_id; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_els_req_tmpl ; 
 int /*<<< orphan*/  memcpy (struct fchs_s*,int /*<<< orphan*/ *,int) ; 

void
fc_els_req_build(struct fchs_s *fchs, u32 d_id, u32 s_id, __be16 ox_id)
{
	memcpy(fchs, &fc_els_req_tmpl, sizeof(struct fchs_s));
	fchs->d_id = (d_id);
	fchs->s_id = (s_id);
	fchs->ox_id = cpu_to_be16(ox_id);
}