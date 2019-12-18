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
struct v4l2_capability {int capabilities; int device_caps; char* card; char* bus_info; } ;
struct dstr {char const* array; } ;
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VIDIOC_QUERYCAP ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,int) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 size_t obs_property_list_add_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  obs_property_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_property_list_item_disable (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_close (int) ; 
 int v4l2_ioctl (int,int /*<<< orphan*/ ,struct v4l2_capability*) ; 
 int v4l2_open (char const*,int) ; 

__attribute__((used)) static void v4l2_device_list(obs_property_t *prop, obs_data_t *settings)
{
	DIR *dirp;
	struct dirent *dp;
	struct dstr device;
	bool cur_device_found;
	size_t cur_device_index;
	const char *cur_device_name;

#ifdef __FreeBSD__
	dirp = opendir("/dev");
#else
	dirp = opendir("/sys/class/video4linux");
#endif
	if (!dirp)
		return;

	cur_device_found = false;
	cur_device_name = obs_data_get_string(settings, "device_id");

	obs_property_list_clear(prop);

	dstr_init_copy(&device, "/dev/");

	while ((dp = readdir(dirp)) != NULL) {
		int fd;
		uint32_t caps;
		struct v4l2_capability video_cap;

#ifdef __FreeBSD__
		if (strstr(dp->d_name, "video") == NULL)
			continue;
#endif

		if (dp->d_type == DT_DIR)
			continue;

		dstr_resize(&device, 5);
		dstr_cat(&device, dp->d_name);

		if ((fd = v4l2_open(device.array, O_RDWR | O_NONBLOCK)) == -1) {
			blog(LOG_INFO, "Unable to open %s", device.array);
			continue;
		}

		if (v4l2_ioctl(fd, VIDIOC_QUERYCAP, &video_cap) == -1) {
			blog(LOG_INFO, "Failed to query capabilities for %s",
			     device.array);
			v4l2_close(fd);
			continue;
		}

#ifndef V4L2_CAP_DEVICE_CAPS
		caps = video_cap.capabilities;
#else
		/* ... since Linux 3.3 */
		caps = (video_cap.capabilities & V4L2_CAP_DEVICE_CAPS)
			       ? video_cap.device_caps
			       : video_cap.capabilities;
#endif

		if (!(caps & V4L2_CAP_VIDEO_CAPTURE)) {
			blog(LOG_INFO, "%s seems to not support video capture",
			     device.array);
			v4l2_close(fd);
			continue;
		}

		/* make sure device names are unique */
		char unique_device_name[68];
		sprintf(unique_device_name, "%s (%s)", video_cap.card,
			video_cap.bus_info);
		obs_property_list_add_string(prop, unique_device_name,
					     device.array);
		blog(LOG_INFO, "Found device '%s' at %s", video_cap.card,
		     device.array);

		/* check if this is the currently used device */
		if (cur_device_name && !strcmp(cur_device_name, device.array))
			cur_device_found = true;

		v4l2_close(fd);
	}

	/* add currently selected device if not present, but disable it ... */
	if (!cur_device_found && cur_device_name && strlen(cur_device_name)) {
		cur_device_index = obs_property_list_add_string(
			prop, cur_device_name, cur_device_name);
		obs_property_list_item_disable(prop, cur_device_index, true);
	}

	closedir(dirp);
	dstr_free(&device);
}