#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num_buffers; int /*<<< orphan*/  buffer_size; } ;
struct zoran_fh {TYPE_1__ buffers; int /*<<< orphan*/  map_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZORAN_MAP_MODE_RAW ; 
 int /*<<< orphan*/  v4l_bufsize ; 
 int /*<<< orphan*/  v4l_nbufs ; 

__attribute__((used)) static void map_mode_raw(struct zoran_fh *fh)
{
	fh->map_mode = ZORAN_MAP_MODE_RAW;
	fh->buffers.buffer_size = v4l_bufsize;
	fh->buffers.num_buffers = v4l_nbufs;
}