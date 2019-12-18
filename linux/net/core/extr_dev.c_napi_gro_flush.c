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
struct napi_struct {unsigned long gro_bitmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_gro_flush_chain (struct napi_struct*,unsigned int,int) ; 
 unsigned int ffs (unsigned long) ; 

void napi_gro_flush(struct napi_struct *napi, bool flush_old)
{
	unsigned long bitmask = napi->gro_bitmask;
	unsigned int i, base = ~0U;

	while ((i = ffs(bitmask)) != 0) {
		bitmask >>= i;
		base += i;
		__napi_gro_flush_chain(napi, base, flush_old);
	}
}