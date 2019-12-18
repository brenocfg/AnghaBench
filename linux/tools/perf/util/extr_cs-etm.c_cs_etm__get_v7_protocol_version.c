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

/* Variables and functions */
 int /*<<< orphan*/  CS_ETM_PROTO_ETMV3 ; 
 int /*<<< orphan*/  CS_ETM_PROTO_PTM ; 
 int /*<<< orphan*/  ETMIDR_PTM_VERSION ; 

__attribute__((used)) static u32 cs_etm__get_v7_protocol_version(u32 etmidr)
{
	etmidr &= ETMIDR_PTM_VERSION;

	if (etmidr == ETMIDR_PTM_VERSION)
		return CS_ETM_PROTO_PTM;

	return CS_ETM_PROTO_ETMV3;
}