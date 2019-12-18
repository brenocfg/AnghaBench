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
typedef  int /*<<< orphan*/  u64 ;
struct yfs_xdr_u64 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct yfs_xdr_u64 u64_to_xdr (int /*<<< orphan*/ ) ; 
 int xdr_size (struct yfs_xdr_u64*) ; 

__attribute__((used)) static __be32 *xdr_encode_u64(__be32 *bp, u64 n)
{
	struct yfs_xdr_u64 *x = (void *)bp;

	*x = u64_to_xdr(n);
	return bp + xdr_size(x);
}