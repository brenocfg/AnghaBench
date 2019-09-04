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
 int EMSGSIZE ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_zero ; 

__attribute__((used)) static inline int
encode_item_not_present(struct xdr_stream *xdr)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, sizeof(*p));
	if (unlikely(!p))
		return -EMSGSIZE;

	*p = xdr_zero;
	return 0;
}