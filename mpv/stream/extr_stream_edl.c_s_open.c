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
struct stream {char* demuxer; } ;

/* Variables and functions */
 int STREAM_OK ; 

__attribute__((used)) static int s_open (struct stream *stream)
{
    stream->demuxer = "edl";

    return STREAM_OK;
}