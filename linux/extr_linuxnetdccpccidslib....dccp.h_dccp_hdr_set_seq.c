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
typedef  int u64 ;
struct dccp_hdr_ext {int /*<<< orphan*/  dccph_seq_low; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_seq; scalar_t__ dccph_seq2; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int const) ; 
 int /*<<< orphan*/  htons (int const) ; 

__attribute__((used)) static inline void dccp_hdr_set_seq(struct dccp_hdr *dh, const u64 gss)
{
	struct dccp_hdr_ext *dhx = (struct dccp_hdr_ext *)((void *)dh +
							   sizeof(*dh));
	dh->dccph_seq2 = 0;
	dh->dccph_seq = htons((gss >> 32) & 0xfffff);
	dhx->dccph_seq_low = htonl(gss & 0xffffffff);
}