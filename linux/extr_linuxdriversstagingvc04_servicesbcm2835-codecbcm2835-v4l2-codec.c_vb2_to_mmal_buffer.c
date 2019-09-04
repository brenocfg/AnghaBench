#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  timestamp; TYPE_1__* planes; } ;
struct vb2_v4l2_buffer {int flags; TYPE_2__ vb2_buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  mmal_flags; int /*<<< orphan*/  length; } ;
struct m2m_mmal_buffer {TYPE_3__ mmal; } ;
struct TYPE_4__ {int /*<<< orphan*/  bytesused; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_EOS ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_FRAME_END ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_KEYFRAME ; 
 int /*<<< orphan*/  MMAL_TIME_UNKNOWN ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int V4L2_BUF_FLAG_LAST ; 

__attribute__((used)) static void vb2_to_mmal_buffer(struct m2m_mmal_buffer *buf,
			       struct vb2_v4l2_buffer *vb2)
{
	buf->mmal.mmal_flags = 0;
	if (vb2->flags & V4L2_BUF_FLAG_KEYFRAME)
		buf->mmal.mmal_flags |= MMAL_BUFFER_HEADER_FLAG_KEYFRAME;

	/*
	 * Adding this means that the data must be framed correctly as one frame
	 * per buffer. The underlying decoder has no such requirement, but it
	 * will reduce latency as the bistream parser will be kicked immediately
	 * to parse the frame, rather than relying on its own heuristics for
	 * when to wake up.
	 */
	buf->mmal.mmal_flags |= MMAL_BUFFER_HEADER_FLAG_FRAME_END;

	buf->mmal.length = vb2->vb2_buf.planes[0].bytesused;
	/*
	 * Minor ambiguity in the V4L2 spec as to whether passing in a 0 length
	 * buffer, or one with V4L2_BUF_FLAG_LAST set denotes end of stream.
	 * Handle either.
	 */
	if (!buf->mmal.length || vb2->flags & V4L2_BUF_FLAG_LAST)
		buf->mmal.mmal_flags |= MMAL_BUFFER_HEADER_FLAG_EOS;

	buf->mmal.pts = vb2->vb2_buf.timestamp;
	buf->mmal.dts = MMAL_TIME_UNKNOWN;
}