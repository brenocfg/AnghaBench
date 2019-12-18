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
typedef  int uint32_t ;
struct v4l2_data {int dev; int resolution; int framerate; int width; int height; int /*<<< orphan*/  thread; int /*<<< orphan*/  event; int /*<<< orphan*/  buffers; int /*<<< orphan*/  linesize; int /*<<< orphan*/  pixfmt; int /*<<< orphan*/  dv_timing; int /*<<< orphan*/  standard; int /*<<< orphan*/  input; int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  OS_EVENT_TYPE_MANUAL ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  V4L2_FOURCC_STR (int /*<<< orphan*/ ) ; 
 int V4L2_IN_CAP_DV_TIMINGS ; 
 int V4L2_IN_CAP_STD ; 
 scalar_t__ VIDEO_FORMAT_NONE ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ os_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v4l2_data*) ; 
 scalar_t__ v4l2_create_mmap (int,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_get_input_caps (int,int,int*) ; 
 int v4l2_open (int /*<<< orphan*/ ,int) ; 
 scalar_t__ v4l2_set_dv_timing (int,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_set_format (int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_set_framerate (int,int*) ; 
 scalar_t__ v4l2_set_input (int,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_set_standard (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_terminate (struct v4l2_data*) ; 
 int /*<<< orphan*/  v4l2_thread ; 
 scalar_t__ v4l2_to_obs_video_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_unpack_tuple (int*,int*,int) ; 

__attribute__((used)) static void v4l2_init(struct v4l2_data *data)
{
	uint32_t input_caps;
	int fps_num, fps_denom;

	blog(LOG_INFO, "Start capture from %s", data->device_id);
	data->dev = v4l2_open(data->device_id, O_RDWR | O_NONBLOCK);
	if (data->dev == -1) {
		blog(LOG_ERROR, "Unable to open device");
		goto fail;
	}

	/* set input */
	if (v4l2_set_input(data->dev, &data->input) < 0) {
		blog(LOG_ERROR, "Unable to set input %d", data->input);
		goto fail;
	}
	blog(LOG_INFO, "Input: %d", data->input);
	if (v4l2_get_input_caps(data->dev, -1, &input_caps) < 0) {
		blog(LOG_ERROR, "Unable to get input capabilities");
		goto fail;
	}

	/* set video standard if supported */
	if (input_caps & V4L2_IN_CAP_STD) {
		if (v4l2_set_standard(data->dev, &data->standard) < 0) {
			blog(LOG_ERROR, "Unable to set video standard");
			goto fail;
		}
		data->resolution = -1;
		data->framerate = -1;
	}
	/* set dv timing if supported */
	if (input_caps & V4L2_IN_CAP_DV_TIMINGS) {
		if (v4l2_set_dv_timing(data->dev, &data->dv_timing) < 0) {
			blog(LOG_ERROR, "Unable to set dv timing");
			goto fail;
		}
		data->resolution = -1;
		data->framerate = -1;
	}

	/* set pixel format and resolution */
	if (v4l2_set_format(data->dev, &data->resolution, &data->pixfmt,
			    &data->linesize) < 0) {
		blog(LOG_ERROR, "Unable to set format");
		goto fail;
	}
	if (v4l2_to_obs_video_format(data->pixfmt) == VIDEO_FORMAT_NONE) {
		blog(LOG_ERROR, "Selected video format not supported");
		goto fail;
	}
	v4l2_unpack_tuple(&data->width, &data->height, data->resolution);
	blog(LOG_INFO, "Resolution: %dx%d", data->width, data->height);
	blog(LOG_INFO, "Pixelformat: %s", V4L2_FOURCC_STR(data->pixfmt));
	blog(LOG_INFO, "Linesize: %d Bytes", data->linesize);

	/* set framerate */
	if (v4l2_set_framerate(data->dev, &data->framerate) < 0) {
		blog(LOG_ERROR, "Unable to set framerate");
		goto fail;
	}
	v4l2_unpack_tuple(&fps_num, &fps_denom, data->framerate);
	blog(LOG_INFO, "Framerate: %.2f fps", (float)fps_denom / fps_num);

	/* map buffers */
	if (v4l2_create_mmap(data->dev, &data->buffers) < 0) {
		blog(LOG_ERROR, "Failed to map buffers");
		goto fail;
	}

	/* start the capture thread */
	if (os_event_init(&data->event, OS_EVENT_TYPE_MANUAL) != 0)
		goto fail;
	if (pthread_create(&data->thread, NULL, v4l2_thread, data) != 0)
		goto fail;
	return;
fail:
	blog(LOG_ERROR, "Initialization failed");
	v4l2_terminate(data);
}