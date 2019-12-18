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

/* Variables and functions */
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void encode_ftype3(struct xdr_stream *xdr, const u32 type)
{
	encode_uint32(xdr, type);
}