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
typedef  scalar_t__ u32 ;
struct nfsd4_slot {int dummy; } ;
struct nfsd4_channel_attrs {scalar_t__ maxresp_cached; } ;

/* Variables and functions */
 scalar_t__ NFSD_MIN_HDR_SEQ_SZ ; 

__attribute__((used)) static inline u32 slot_bytes(struct nfsd4_channel_attrs *ca)
{
	u32 size;

	if (ca->maxresp_cached < NFSD_MIN_HDR_SEQ_SZ)
		size = 0;
	else
		size = ca->maxresp_cached - NFSD_MIN_HDR_SEQ_SZ;
	return size + sizeof(struct nfsd4_slot);
}