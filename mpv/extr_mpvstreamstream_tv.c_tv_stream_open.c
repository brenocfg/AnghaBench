#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* demuxer; int /*<<< orphan*/  close; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int STREAM_OK ; 
 int /*<<< orphan*/  tv_stream_close ; 

__attribute__((used)) static int
tv_stream_open (stream_t *stream)
{

  stream->close=tv_stream_close;
  stream->demuxer = "tv";

  return STREAM_OK;
}