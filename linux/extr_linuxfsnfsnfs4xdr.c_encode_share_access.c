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
struct xdr_stream {int dummy; } ;
typedef  void* __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void** reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_share_access(struct xdr_stream *xdr, u32 share_access)
{
	__be32 *p;

	p = reserve_space(xdr, 8);
	*p++ = cpu_to_be32(share_access);
	*p = cpu_to_be32(0);		/* for linux, share_deny = 0 always */
}