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
struct stream_info {int /*<<< orphan*/  lock; scalar_t__ cumm_bytes; void* prev; void* status; } ;

/* Variables and functions */
 void* STREAM_UN_INIT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void sst_clean_stream(struct stream_info *stream)
{
	stream->status = STREAM_UN_INIT;
	stream->prev = STREAM_UN_INIT;
	mutex_lock(&stream->lock);
	stream->cumm_bytes = 0;
	mutex_unlock(&stream->lock);
}