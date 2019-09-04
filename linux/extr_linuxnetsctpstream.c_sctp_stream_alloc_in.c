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
struct sctp_stream_in {int dummy; } ;
struct sctp_stream {scalar_t__ incnt; struct flex_array* in; } ;
struct flex_array {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 struct flex_array* fa_alloc (size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fa_copy (struct flex_array*,struct flex_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fa_free (struct flex_array*) ; 
 int /*<<< orphan*/  fa_zero (struct flex_array*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sctp_stream_alloc_in(struct sctp_stream *stream, __u16 incnt,
				gfp_t gfp)
{
	struct flex_array *in;
	size_t elem_size = sizeof(struct sctp_stream_in);

	in = fa_alloc(elem_size, incnt, gfp);
	if (!in)
		return -ENOMEM;

	if (stream->in) {
		fa_copy(in, stream->in, 0, min(incnt, stream->incnt));
		fa_free(stream->in);
	}

	if (incnt > stream->incnt)
		fa_zero(in, stream->incnt, (incnt - stream->incnt));

	stream->in = in;

	return 0;
}