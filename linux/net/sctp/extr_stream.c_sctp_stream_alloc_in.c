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
struct sctp_stream {scalar_t__ incnt; int /*<<< orphan*/  in; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int genradix_prealloc (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_stream_alloc_in(struct sctp_stream *stream, __u16 incnt,
				gfp_t gfp)
{
	int ret;

	if (incnt <= stream->incnt)
		return 0;

	ret = genradix_prealloc(&stream->in, incnt, gfp);
	if (ret)
		return ret;

	stream->incnt = incnt;
	return 0;
}