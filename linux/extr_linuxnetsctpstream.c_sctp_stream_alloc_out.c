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
struct sctp_stream_out {int dummy; } ;
struct sctp_stream {size_t outcnt; struct flex_array* out; scalar_t__ out_curr; } ;
struct flex_array {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct flex_array* fa_alloc (size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fa_copy (struct flex_array*,struct flex_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fa_free (struct flex_array*) ; 
 size_t fa_index (struct flex_array*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  fa_zero (struct flex_array*,scalar_t__,scalar_t__) ; 
 scalar_t__ flex_array_get (struct flex_array*,size_t) ; 
 int /*<<< orphan*/  min (scalar_t__,size_t) ; 

__attribute__((used)) static int sctp_stream_alloc_out(struct sctp_stream *stream, __u16 outcnt,
				 gfp_t gfp)
{
	struct flex_array *out;
	size_t elem_size = sizeof(struct sctp_stream_out);

	out = fa_alloc(elem_size, outcnt, gfp);
	if (!out)
		return -ENOMEM;

	if (stream->out) {
		fa_copy(out, stream->out, 0, min(outcnt, stream->outcnt));
		if (stream->out_curr) {
			size_t index = fa_index(stream->out, stream->out_curr,
						stream->outcnt);

			BUG_ON(index == stream->outcnt);
			stream->out_curr = flex_array_get(out, index);
		}
		fa_free(stream->out);
	}

	if (outcnt > stream->outcnt)
		fa_zero(out, stream->outcnt, (outcnt - stream->outcnt));

	stream->out = out;

	return 0;
}