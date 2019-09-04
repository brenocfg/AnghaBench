#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_buffer_entry ;
struct TYPE_16__ {long long tv_sec; long long tv_usec; } ;
struct v4l2_buffer {int index; int flags; int /*<<< orphan*/  bytesused; TYPE_1__ timestamp; void* memory; void* type; } ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_18__ {int sizeimage; } ;
struct TYPE_19__ {TYPE_3__ pix; } ;
struct TYPE_20__ {struct v4l2_buffer type; TYPE_4__ fmt; } ;
struct TYPE_22__ {int streamon; int video_cnt; int video_buffer_size_max; int mapcount; long long first_frame; long long curr_frame; long long audio_skew; long long audio_skew_measure_time; long long audio_skew_factor; int video_buffer_size_current; int video_tail; size_t video_head; long long dropped_frames_timeshift; int audio_null_blocks_inserted; int audio_usecs_per_block; scalar_t__ video_fd; TYPE_2__* map; TYPE_9__* video_ringbuffer; int /*<<< orphan*/  audio_mutex; scalar_t__ audio_insert_null_samples; scalar_t__ immediate_mode; int /*<<< orphan*/  video_buffer_mutex; int /*<<< orphan*/  audio_cnt; int /*<<< orphan*/  skew_mutex; TYPE_6__* tv_param; scalar_t__ frames; scalar_t__ shutdown; int /*<<< orphan*/  audio_grabber_thread; TYPE_5__ format; } ;
typedef  TYPE_7__ priv_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_23__ {unsigned char* data; long long timestamp; } ;
struct TYPE_21__ {scalar_t__ audio; } ;
struct TYPE_17__ {int /*<<< orphan*/  addr; struct v4l2_buffer buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 long long MAX_SKEW_DELTA ; 
 int /*<<< orphan*/  MP_ERR (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  MP_TRACE (TYPE_7__*,char*,int,double,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_7__*,char*) ; 
 int V4L2_BUF_FLAG_DONE ; 
 int V4L2_BUF_FLAG_MAPPED ; 
 int V4L2_BUF_FLAG_QUEUED ; 
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 void* V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  VIDIOC_DQBUF ; 
 int /*<<< orphan*/  VIDIOC_QBUF ; 
 int /*<<< orphan*/  VIDIOC_QUERYBUF ; 
 int /*<<< orphan*/  VIDIOC_STREAMON ; 
 int /*<<< orphan*/  audio_grabber ; 
 int /*<<< orphan*/  copy_frame (TYPE_7__*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memmove (TYPE_9__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  memset (struct v4l2_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int v4l2_ioctl (scalar_t__,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static void *video_grabber(void *data)
{
    priv_t *priv = (priv_t*)data;
    long long skew, prev_skew, xskew, interval, prev_interval, delta;
    int i;
    int framesize = priv->format.fmt.pix.sizeimage;
    fd_set rdset;
    struct timeval timeout;
    struct v4l2_buffer buf;

    xskew = 0;
    skew = 0;
    interval = 0;
    prev_interval = 0;
    prev_skew = 0;

    MP_VERBOSE(priv, "going to capture\n");
    if (v4l2_ioctl(priv->video_fd, VIDIOC_STREAMON, &(priv->format.type)) < 0) {
        MP_ERR(priv, "ioctl streamon failed: %s\n", mp_strerror(errno));
        return 0;
    }
    priv->streamon = 1;

    if (priv->tv_param->audio) {
        pthread_create(&priv->audio_grabber_thread, NULL, audio_grabber, priv);
    }

    for (priv->frames = 0; !priv->shutdown;)
    {
        int ret;

        while (priv->video_cnt == priv->video_buffer_size_max) {
            usleep(10000);
            if (priv->shutdown) {
                return NULL;
            }
        }

        FD_ZERO (&rdset);
        FD_SET (priv->video_fd, &rdset);

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        i = select(priv->video_fd + 1, &rdset, NULL, NULL, &timeout);
        if (i < 0) {
            MP_ERR(priv, "select failed: %s\n", mp_strerror(errno));
            continue;
        }
        else if (i == 0) {
            MP_ERR(priv, "select timeout\n");
            continue;
        }
        else if (!FD_ISSET(priv->video_fd, &rdset)) {
            continue;
        }

        memset(&buf,0,sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        ret = v4l2_ioctl(priv->video_fd, VIDIOC_DQBUF, &buf);

        if (ret < 0) {
            /*
              if there's no signal, the buffer might me dequeued
              so we query all the buffers to see which one we should
              put back to queue

              observed with saa7134 0.2.8
              don't know if is it a bug or (mis)feature
             */
            MP_ERR(priv, "ioctl dequeue buffer failed: %s, idx = %d\n",
                   mp_strerror(errno), buf.index);
            for (i = 0; i < priv->mapcount; i++) {
                memset(&buf,0,sizeof(buf));
                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_MMAP;
                buf.index = i;
                ret = v4l2_ioctl(priv->video_fd, VIDIOC_QUERYBUF, &buf);
                if (ret < 0) {
                    MP_ERR(priv, "ioctl query buffer failed: %s, idx = %d\n",
                           mp_strerror(errno), buf.index);
                    return 0;
                }
                if ((buf.flags & (V4L2_BUF_FLAG_QUEUED | V4L2_BUF_FLAG_MAPPED | V4L2_BUF_FLAG_DONE)) == V4L2_BUF_FLAG_MAPPED) {
                    if (v4l2_ioctl(priv->video_fd, VIDIOC_QBUF, &(priv->map[i].buf)) < 0) {
                        MP_ERR(priv, "ioctl queue buffer failed: %s\n",
                               mp_strerror(errno));
                        return 0;
                    }
                }
            }
            continue;
        }

        /* store the timestamp of the very first frame as reference */
        if (!priv->frames++) {
            if (priv->tv_param->audio) pthread_mutex_lock(&priv->skew_mutex);
            priv->first_frame = buf.timestamp.tv_sec * 1000000LL + buf.timestamp.tv_usec;
            if (priv->tv_param->audio) pthread_mutex_unlock(&priv->skew_mutex);
        }
        priv->curr_frame = buf.timestamp.tv_sec * 1000000LL + buf.timestamp.tv_usec;
//        fprintf(stderr, "idx = %d, ts = %f\n", buf.index, (double)(priv->curr_frame) / 1e6);

        interval = priv->curr_frame - priv->first_frame;
        delta = interval - prev_interval;

        // interpolate the skew in time
        if (priv->tv_param->audio) pthread_mutex_lock(&priv->skew_mutex);
        xskew = priv->audio_skew + (interval - priv->audio_skew_measure_time)*priv->audio_skew_factor;
        if (priv->tv_param->audio) pthread_mutex_unlock(&priv->skew_mutex);
            // correct extreme skew changes to avoid (especially) moving backwards in time
        if (xskew - prev_skew > delta*MAX_SKEW_DELTA) {
            skew = prev_skew + delta*MAX_SKEW_DELTA;
        } else if (xskew - prev_skew < -delta*MAX_SKEW_DELTA) {
            skew = prev_skew - delta*MAX_SKEW_DELTA;
        } else {
            skew = xskew;
        }

        MP_TRACE(priv, "\nfps = %f, interval = %f, a_skew = %f, corr_skew = %f\n",
               delta ? (double)1e6/delta : -1,
               (double)1e-6*interval, (double)1e-6*xskew, (double)1e-6*skew);
        MP_TRACE(priv, "vcnt = %d, acnt = %d\n", priv->video_cnt, priv->audio_cnt);

        prev_skew = skew;
        prev_interval = interval;

        /* allocate a new buffer, if needed */
        pthread_mutex_lock(&priv->video_buffer_mutex);
        if (priv->video_buffer_size_current < priv->video_buffer_size_max) {
            if (priv->video_cnt == priv->video_buffer_size_current) {
                unsigned char *newbuf = malloc(framesize);
                if (newbuf) {
                    memmove(priv->video_ringbuffer+priv->video_tail+1, priv->video_ringbuffer+priv->video_tail,
                            (priv->video_buffer_size_current-priv->video_tail)*sizeof(video_buffer_entry));
                    priv->video_ringbuffer[priv->video_tail].data = newbuf;
                    if ((priv->video_head >= priv->video_tail) && (priv->video_cnt > 0)) priv->video_head++;
                    priv->video_buffer_size_current++;
                }
            }
        }
        pthread_mutex_unlock(&priv->video_buffer_mutex);

        if (priv->video_cnt == priv->video_buffer_size_current) {
            MP_ERR(priv, "\nvideo buffer full - dropping frame\n");
            if (!priv->immediate_mode || priv->audio_insert_null_samples) {
                pthread_mutex_lock(&priv->audio_mutex);
                priv->dropped_frames_timeshift += delta;
                pthread_mutex_unlock(&priv->audio_mutex);
            }
        } else {
            if (priv->immediate_mode) {
                priv->video_ringbuffer[priv->video_tail].timestamp = interval - skew;
            } else {
                // compensate for audio skew
                // negative skew => there are more audio samples, increase interval
                // positive skew => less samples, shorten the interval
                priv->video_ringbuffer[priv->video_tail].timestamp = interval - skew;
                if (priv->audio_insert_null_samples && priv->video_ringbuffer[priv->video_tail].timestamp > 0) {
                    pthread_mutex_lock(&priv->audio_mutex);
                    priv->video_ringbuffer[priv->video_tail].timestamp +=
                        (priv->audio_null_blocks_inserted
                         - priv->dropped_frames_timeshift/priv->audio_usecs_per_block)
                        *priv->audio_usecs_per_block;
                    pthread_mutex_unlock(&priv->audio_mutex);
                }
            }
            copy_frame(priv, priv->video_ringbuffer+priv->video_tail, priv->map[buf.index].addr,buf.bytesused);
            priv->video_tail = (priv->video_tail+1)%priv->video_buffer_size_current;
            priv->video_cnt++;
        }
        if (v4l2_ioctl(priv->video_fd, VIDIOC_QBUF, &buf) < 0) {
            MP_ERR(priv, "ioctl queue buffer failed: %s\n", mp_strerror(errno));
            return 0;
        }
    }
    return NULL;
}