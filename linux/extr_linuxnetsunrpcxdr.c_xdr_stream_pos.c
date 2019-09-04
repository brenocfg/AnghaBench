#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {scalar_t__ nwords; TYPE_1__* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ XDR_QUADLEN (int /*<<< orphan*/ ) ; 

unsigned int xdr_stream_pos(const struct xdr_stream *xdr)
{
	return (unsigned int)(XDR_QUADLEN(xdr->buf->len) - xdr->nwords) << 2;
}