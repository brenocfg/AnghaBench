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
typedef  int u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int HEADER_TSTAMP_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 compute_cycle_count(__be32 ctx_header_tstamp)
{
	u32 tstamp = be32_to_cpu(ctx_header_tstamp) & HEADER_TSTAMP_MASK;
	return (((tstamp >> 13) & 0x07) * 8000) + (tstamp & 0x1fff);
}