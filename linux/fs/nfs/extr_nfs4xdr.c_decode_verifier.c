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
 int /*<<< orphan*/  NFS4_VERIFIER_SIZE ; 
 int decode_opaque_fixed (struct xdr_stream*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_verifier(struct xdr_stream *xdr, void *verifier)
{
	return decode_opaque_fixed(xdr, verifier, NFS4_VERIFIER_SIZE);
}