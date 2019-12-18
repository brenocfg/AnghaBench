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
struct rchan_callbacks {scalar_t__ remove_buf_file; scalar_t__ create_buf_file; scalar_t__ buf_unmapped; scalar_t__ buf_mapped; scalar_t__ subbuf_start; } ;
struct rchan {struct rchan_callbacks* cb; } ;

/* Variables and functions */
 scalar_t__ buf_mapped_default_callback ; 
 scalar_t__ buf_unmapped_default_callback ; 
 scalar_t__ create_buf_file_default_callback ; 
 struct rchan_callbacks default_channel_callbacks ; 
 scalar_t__ remove_buf_file_default_callback ; 
 scalar_t__ subbuf_start_default_callback ; 

__attribute__((used)) static void setup_callbacks(struct rchan *chan,
				   struct rchan_callbacks *cb)
{
	if (!cb) {
		chan->cb = &default_channel_callbacks;
		return;
	}

	if (!cb->subbuf_start)
		cb->subbuf_start = subbuf_start_default_callback;
	if (!cb->buf_mapped)
		cb->buf_mapped = buf_mapped_default_callback;
	if (!cb->buf_unmapped)
		cb->buf_unmapped = buf_unmapped_default_callback;
	if (!cb->create_buf_file)
		cb->create_buf_file = create_buf_file_default_callback;
	if (!cb->remove_buf_file)
		cb->remove_buf_file = remove_buf_file_default_callback;
	chan->cb = cb;
}