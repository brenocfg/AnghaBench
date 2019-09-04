#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_buffer_entry ;
struct TYPE_19__ {int /*<<< orphan*/  offset; } ;
struct v4l2_requestbuffers {unsigned int count; unsigned int index; int flags; scalar_t__ length; TYPE_1__ m; void* memory; void* type; } ;
struct map {int dummy; } ;
struct TYPE_23__ {int width; int height; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_24__ {TYPE_5__ pix; } ;
struct TYPE_22__ {TYPE_6__ fmt; } ;
struct TYPE_20__ {unsigned int blocksize; double samplerate; double channels; double bytes_per_sample; } ;
struct TYPE_25__ {int video_buffer_size_max; unsigned int aud_skew_cnt; int audio_buffer_size; double audio_secs_per_block; int audio_usecs_per_block; int first; scalar_t__ audio_skew; scalar_t__ first_frame; scalar_t__ audio_skew_measure_time; scalar_t__ shutdown; TYPE_14__* map; int /*<<< orphan*/  video_fd; int /*<<< orphan*/  mapcount; scalar_t__ video_cnt; scalar_t__ video_tail; scalar_t__ video_head; int /*<<< orphan*/  video_buffer_mutex; void* video_ringbuffer; TYPE_4__ format; TYPE_3__* tv_param; int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  skew_mutex; scalar_t__ dropped_frames_compensated; scalar_t__ dropped_frames_timeshift; scalar_t__ audio_insert_null_samples; scalar_t__ audio_null_blocks_inserted; scalar_t__ audio_sent_blocks_total; scalar_t__ audio_recv_blocks_total; scalar_t__ audio_skew_delta_total; scalar_t__ audio_skew_total; scalar_t__ audio_drop; scalar_t__ audio_cnt; scalar_t__ audio_tail; scalar_t__ audio_head; TYPE_2__ audio_in; void* audio_ringbuffer; void* audio_skew_delta_buffer; void* audio_skew_buffer; int /*<<< orphan*/  audio_initialized; } ;
typedef  TYPE_7__ priv_t ;
struct TYPE_21__ {scalar_t__ audio; } ;
struct TYPE_18__ {scalar_t__ addr; struct v4l2_requestbuffers buf; scalar_t__ len; } ;

/* Variables and functions */
 unsigned int BUFFER_COUNT ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MP_ERR (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_7__*,char*,int,int) ; 
 int /*<<< orphan*/  MP_WARN (TYPE_7__*,char*) ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 void* V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  VIDIOC_QBUF ; 
 int /*<<< orphan*/  VIDIOC_QUERYBUF ; 
 int /*<<< orphan*/  VIDIOC_REQBUFS ; 
 void* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_14__*) ; 
 int get_capture_buffer_size (TYPE_7__*) ; 
 int getfps (TYPE_7__*) ; 
 int /*<<< orphan*/  init_audio (TYPE_7__*) ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int pixfmt2depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mute (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_audio_buffer_sizes (TYPE_7__*) ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_requestbuffers*) ; 
 scalar_t__ v4l2_mmap (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start(priv_t *priv)
{
    struct v4l2_requestbuffers request;
    unsigned int i;

    /* setup audio parameters */

    init_audio(priv);
    if (priv->tv_param->audio && !priv->audio_initialized) return 0;

    priv->video_buffer_size_max = get_capture_buffer_size(priv);

    if (priv->tv_param->audio) {
        setup_audio_buffer_sizes(priv);
        priv->audio_skew_buffer = calloc(priv->aud_skew_cnt, sizeof(long long));
        if (!priv->audio_skew_buffer) {
            MP_ERR(priv, "cannot allocate skew buffer: %s\n", mp_strerror(errno));
            return 0;
        }
        priv->audio_skew_delta_buffer = calloc(priv->aud_skew_cnt, sizeof(long long));
        if (!priv->audio_skew_delta_buffer) {
            MP_ERR(priv, "cannot allocate skew buffer: %s\n", mp_strerror(errno));
            return 0;
        }

        priv->audio_ringbuffer = calloc(priv->audio_in.blocksize, priv->audio_buffer_size);
        if (!priv->audio_ringbuffer) {
            MP_ERR(priv, "cannot allocate audio buffer: %s\n", mp_strerror(errno));
            return 0;
        }

        priv->audio_secs_per_block = (double)priv->audio_in.blocksize/(priv->audio_in.samplerate
                                                                    *priv->audio_in.channels
                                                                    *priv->audio_in.bytes_per_sample);
        priv->audio_usecs_per_block = 1e6*priv->audio_secs_per_block;
        priv->audio_head = 0;
        priv->audio_tail = 0;
        priv->audio_cnt = 0;
        priv->audio_drop = 0;
        priv->audio_skew = 0;
        priv->audio_skew_total = 0;
        priv->audio_skew_delta_total = 0;
        priv->audio_recv_blocks_total = 0;
        priv->audio_sent_blocks_total = 0;
        priv->audio_null_blocks_inserted = 0;
        priv->audio_insert_null_samples = 0;
        priv->dropped_frames_timeshift = 0;
        priv->dropped_frames_compensated = 0;

        pthread_mutex_init(&priv->skew_mutex, NULL);
        pthread_mutex_init(&priv->audio_mutex, NULL);
    }

    /* setup video parameters */
    if (priv->tv_param->audio) {
        if (priv->video_buffer_size_max < 3*getfps(priv)*priv->audio_secs_per_block) {
            MP_ERR(priv, "Video buffer shorter than 3 times audio frame duration.\n"
                   "You will probably experience heavy framedrops.\n");
        }
    }

    {
        int bytesperline = priv->format.fmt.pix.width*pixfmt2depth(priv->format.fmt.pix.pixelformat)/8;

        MP_VERBOSE(priv, "Using a ring buffer for maximum %d frames, %d MB total size.\n",
               priv->video_buffer_size_max,
               priv->video_buffer_size_max*priv->format.fmt.pix.height*bytesperline/(1024*1024));
    }

    priv->video_ringbuffer = calloc(priv->video_buffer_size_max, sizeof(video_buffer_entry));
    if (!priv->video_ringbuffer) {
        MP_ERR(priv, "cannot allocate video buffer: %s\n", mp_strerror(errno));
        return 0;
    }
    pthread_mutex_init(&priv->video_buffer_mutex, NULL);

    priv->video_head = 0;
    priv->video_tail = 0;
    priv->video_cnt = 0;

    /* request buffers */
    request.count = BUFFER_COUNT;

    request.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    request.memory = V4L2_MEMORY_MMAP;
    if (v4l2_ioctl(priv->video_fd, VIDIOC_REQBUFS, &request) < 0) {
        MP_ERR(priv, "ioctl request buffers failed: %s\n", mp_strerror(errno));
        return 0;
    }

    /* query buffers */
    if (!(priv->map = calloc(request.count, sizeof(struct map)))) {
        MP_ERR(priv, "malloc capture buffers failed: %s\n",  mp_strerror(errno));
        return 0;
    }

    /* map and queue buffers */
    for (i = 0; i < request.count; i++) {
        priv->map[i].buf.index = i;
        priv->map[i].buf.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        priv->map[i].buf.memory  = V4L2_MEMORY_MMAP;
        if (v4l2_ioctl(priv->video_fd, VIDIOC_QUERYBUF, &(priv->map[i].buf)) < 0) {
            MP_ERR(priv, "ioctl query buffer failed: %s\n", mp_strerror(errno));
            free(priv->map);
            priv->map = NULL;
            return 0;
        }
        priv->map[i].addr = v4l2_mmap (0, priv->map[i].buf.length, PROT_READ |
                                  PROT_WRITE, MAP_SHARED, priv->video_fd, priv->map[i].buf.m.offset);
        if (priv->map[i].addr == MAP_FAILED) {
            MP_ERR(priv, "mmap capture buffer failed: %s\n",  mp_strerror(errno));
            priv->map[i].len = 0;
            return 0;
        }
        priv->map[i].len = priv->map[i].buf.length;
#ifdef HAVE_CLOCK_GETTIME
        priv->clk_id = (priv->map[i].buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC)
                           ? CLOCK_MONOTONIC : CLOCK_REALTIME;
#else
        if (priv->map[i].buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC)
            MP_WARN(priv, "compiled without clock_gettime() that is needed to handle monotone video timestamps from the kernel. Expect desync.\n");
#endif
        /* count up to make sure this is correct every time */
        priv->mapcount++;

        if (v4l2_ioctl(priv->video_fd, VIDIOC_QBUF, &(priv->map[i].buf)) < 0) {
            MP_ERR(priv, "ioctl queue buffer failed: %s\n", mp_strerror(errno));
            return 0;
        }
    }

    /* start audio thread */
    priv->shutdown = 0;
    priv->audio_skew_measure_time = 0;
    priv->first_frame = 0;
    priv->audio_skew = 0;
    priv->first = 1;

    set_mute(priv, 0);

    return 1;
}