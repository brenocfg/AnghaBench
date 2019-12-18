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
struct image_writer_opts {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_PNG ; 

bool image_writer_high_depth(const struct image_writer_opts *opts)
{
    return opts->format == AV_CODEC_ID_PNG;
}