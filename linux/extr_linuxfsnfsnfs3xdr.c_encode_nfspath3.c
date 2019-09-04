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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  xdr_write_pages (struct xdr_stream*,struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void encode_nfspath3(struct xdr_stream *xdr, struct page **pages,
			    const u32 length)
{
	encode_uint32(xdr, length);
	xdr_write_pages(xdr, pages, 0, length);
}