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
typedef  unsigned int u32 ;
struct mpls_shim_hdr {int /*<<< orphan*/  label_stack_entry; } ;

/* Variables and functions */
 unsigned int MPLS_LS_LABEL_SHIFT ; 
 int MPLS_LS_S_SHIFT ; 
 unsigned int MPLS_LS_TC_SHIFT ; 
 unsigned int MPLS_LS_TTL_SHIFT ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 

__attribute__((used)) static inline struct mpls_shim_hdr mpls_entry_encode(u32 label, unsigned ttl, unsigned tc, bool bos)
{
	struct mpls_shim_hdr result;
	result.label_stack_entry =
		cpu_to_be32((label << MPLS_LS_LABEL_SHIFT) |
			    (tc << MPLS_LS_TC_SHIFT) |
			    (bos ? (1 << MPLS_LS_S_SHIFT) : 0) |
			    (ttl << MPLS_LS_TTL_SHIFT));
	return result;
}