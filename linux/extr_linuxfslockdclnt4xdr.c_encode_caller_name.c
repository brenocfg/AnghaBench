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
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  xdr_encode_opaque (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,scalar_t__) ; 

__attribute__((used)) static void encode_caller_name(struct xdr_stream *xdr, const char *name)
{
	/* NB: client-side does not set lock->len */
	u32 length = strlen(name);
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, name, length);
}