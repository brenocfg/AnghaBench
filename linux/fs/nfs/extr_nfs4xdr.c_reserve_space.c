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
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,size_t) ; 

__attribute__((used)) static __be32 *reserve_space(struct xdr_stream *xdr, size_t nbytes)
{
	__be32 *p = xdr_reserve_space(xdr, nbytes);
	BUG_ON(!p);
	return p;
}