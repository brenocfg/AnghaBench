#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int format; unsigned int width; unsigned int height; int full_range; scalar_t__* linesize; scalar_t__* data; int /*<<< orphan*/  color_range_max; int /*<<< orphan*/  color_range_min; int /*<<< orphan*/  color_matrix; } ;
struct vlc_source {TYPE_1__ frame; int /*<<< orphan*/  media_player; } ;
typedef  enum video_range_type { ____Placeholder_video_range_type } video_range_type ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_CS_DEFAULT ; 
 int VIDEO_RANGE_FULL ; 
 int VIDEO_RANGE_PARTIAL ; 
 int convert_vlc_video_format (char*,int*) ; 
 unsigned int get_format_lines (int,unsigned int,size_t) ; 
 int /*<<< orphan*/  libvlc_video_get_size_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  obs_source_frame_free (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_frame_init (TYPE_1__*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  video_format_get_parameters (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned vlcs_video_format(void **p_data, char *chroma, unsigned *width,
				  unsigned *height, unsigned *pitches,
				  unsigned *lines)
{
	struct vlc_source *c = *p_data;
	enum video_format new_format;
	enum video_range_type range;
	bool new_range;
	unsigned new_width = 0;
	unsigned new_height = 0;
	size_t i = 0;

	new_format = convert_vlc_video_format(chroma, &new_range);

	/* This is used because VLC will by default try to use a different
	 * scaling than what the file uses (probably for optimization reasons).
	 * For example, if the file is 1920x1080, it will try to render it by
	 * 1920x1088, which isn't what we want.  Calling libvlc_video_get_size
	 * gets the actual video file's size, and thus fixes the problem.
	 * However this doesn't work with URLs, so if it returns a 0 value, it
	 * shouldn't be used. */
	libvlc_video_get_size_(c->media_player, 0, &new_width, &new_height);

	if (new_width && new_height) {
		*width = new_width;
		*height = new_height;
	}

	/* don't allocate a new frame if format/width/height hasn't changed */
	if (c->frame.format != new_format || c->frame.width != *width ||
	    c->frame.height != *height) {
		obs_source_frame_free(&c->frame);
		obs_source_frame_init(&c->frame, new_format, *width, *height);

		c->frame.format = new_format;
		c->frame.full_range = new_range;
		range = c->frame.full_range ? VIDEO_RANGE_FULL
					    : VIDEO_RANGE_PARTIAL;
		video_format_get_parameters(VIDEO_CS_DEFAULT, range,
					    c->frame.color_matrix,
					    c->frame.color_range_min,
					    c->frame.color_range_max);
	}

	while (c->frame.data[i]) {
		pitches[i] = (unsigned)c->frame.linesize[i];
		lines[i] = get_format_lines(c->frame.format, *height, i);
		i++;
	}

	return 1;
}