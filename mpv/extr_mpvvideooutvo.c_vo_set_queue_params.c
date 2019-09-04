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
struct vo_internal {int /*<<< orphan*/  lock; int /*<<< orphan*/  req_frames; int /*<<< orphan*/  flip_queue_offset; } ;
struct vo {struct vo_internal* in; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPCLAMP (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VO_MAX_REQ_FRAMES ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void vo_set_queue_params(struct vo *vo, int64_t offset_us, int num_req_frames)
{
    struct vo_internal *in = vo->in;
    pthread_mutex_lock(&in->lock);
    in->flip_queue_offset = offset_us;
    in->req_frames = MPCLAMP(num_req_frames, 1, VO_MAX_REQ_FRAMES);
    pthread_mutex_unlock(&in->lock);
}