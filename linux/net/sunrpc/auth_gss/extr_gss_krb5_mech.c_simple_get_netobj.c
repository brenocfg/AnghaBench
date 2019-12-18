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
struct xdr_netobj {unsigned int len; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  ENOMEM ; 
 void const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (void const*) ; 
 int /*<<< orphan*/ * kmemdup (void const*,unsigned int,int /*<<< orphan*/ ) ; 
 void* simple_get_bytes (void const*,void const*,unsigned int*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static const void *
simple_get_netobj(const void *p, const void *end, struct xdr_netobj *res)
{
	const void *q;
	unsigned int len;

	p = simple_get_bytes(p, end, &len, sizeof(len));
	if (IS_ERR(p))
		return p;
	q = (const void *)((const char *)p + len);
	if (unlikely(q > end || q < p))
		return ERR_PTR(-EFAULT);
	res->data = kmemdup(p, len, GFP_NOFS);
	if (unlikely(res->data == NULL))
		return ERR_PTR(-ENOMEM);
	res->len = len;
	return q;
}