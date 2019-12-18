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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  RDP_CAPLEN_BRUSHCACHE ; 
 int /*<<< orphan*/  RDP_CAPSET_BRUSHCACHE ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdp_out_brushcache_caps(STREAM s)
{
	out_uint16_le(s, RDP_CAPSET_BRUSHCACHE);
	out_uint16_le(s, RDP_CAPLEN_BRUSHCACHE);
	out_uint32_le(s, 1);	/* cache type */
}