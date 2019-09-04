#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mp_media_info {int speed; int /*<<< orphan*/  is_local_file; int /*<<< orphan*/  buffering; int /*<<< orphan*/  force_range; int /*<<< orphan*/  v_preload_cb; int /*<<< orphan*/  stop_cb; int /*<<< orphan*/  a_cb; int /*<<< orphan*/  v_cb; int /*<<< orphan*/  opaque; } ;
struct TYPE_6__ {int speed; int /*<<< orphan*/  is_local_file; int /*<<< orphan*/  buffering; int /*<<< orphan*/  force_range; int /*<<< orphan*/  v_preload_cb; int /*<<< orphan*/  stop_cb; int /*<<< orphan*/  a_cb; int /*<<< orphan*/  v_cb; int /*<<< orphan*/  opaque; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ mp_media_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_register_all () ; 
 int /*<<< orphan*/  avcodec_register_all () ; 
 int /*<<< orphan*/  avdevice_register_all () ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 scalar_t__ base_sys_ts ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_media_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_media_init_internal (TYPE_1__*,struct mp_media_info const*) ; 
 scalar_t__ os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 

bool mp_media_init(mp_media_t *media, const struct mp_media_info *info)
{
	memset(media, 0, sizeof(*media));
	pthread_mutex_init_value(&media->mutex);
	media->opaque = info->opaque;
	media->v_cb = info->v_cb;
	media->a_cb = info->a_cb;
	media->stop_cb = info->stop_cb;
	media->v_preload_cb = info->v_preload_cb;
	media->force_range = info->force_range;
	media->buffering = info->buffering;
	media->speed = info->speed;
	media->is_local_file = info->is_local_file;

	if (!info->is_local_file || media->speed < 1 || media->speed > 200)
		media->speed = 100;

	static bool initialized = false;
	if (!initialized) {
		av_register_all();
		avdevice_register_all();
		avcodec_register_all();
		avformat_network_init();
		initialized = true;
	}

	if (!base_sys_ts)
		base_sys_ts = (int64_t)os_gettime_ns();

	if (!mp_media_init_internal(media, info)) {
		mp_media_free(media);
		return false;
	}

	return true;
}