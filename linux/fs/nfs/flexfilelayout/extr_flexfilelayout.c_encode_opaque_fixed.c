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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ xdr_stream_encode_opaque_fixed (struct xdr_stream*,void const*,size_t) ; 

__attribute__((used)) static void
encode_opaque_fixed(struct xdr_stream *xdr, const void *buf, size_t len)
{
	WARN_ON_ONCE(xdr_stream_encode_opaque_fixed(xdr, buf, len) < 0);
}