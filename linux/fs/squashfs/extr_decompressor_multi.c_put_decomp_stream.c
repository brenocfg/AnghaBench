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
struct squashfs_stream {int /*<<< orphan*/  wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  strm_list; } ;
struct decomp_stream {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_decomp_stream(struct decomp_stream *decomp_strm,
				struct squashfs_stream *stream)
{
	mutex_lock(&stream->mutex);
	list_add(&decomp_strm->list, &stream->strm_list);
	mutex_unlock(&stream->mutex);
	wake_up(&stream->wait);
}