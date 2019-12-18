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
typedef  int /*<<< orphan*/  uint32_t ;
struct video_frame {int dummy; } ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
 scalar_t__ bzalloc (int) ; 
 int /*<<< orphan*/  video_frame_init (struct video_frame*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct video_frame *
video_frame_create(enum video_format format, uint32_t width, uint32_t height)
{
	struct video_frame *frame;

	frame = (struct video_frame *)bzalloc(sizeof(struct video_frame));
	video_frame_init(frame, format, width, height);
	return frame;
}