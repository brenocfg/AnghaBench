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
struct flv_output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_audio_header (struct flv_output*) ; 
 int /*<<< orphan*/  write_meta_data (struct flv_output*) ; 
 int /*<<< orphan*/  write_video_header (struct flv_output*) ; 

__attribute__((used)) static void write_headers(struct flv_output *stream)
{
	write_meta_data(stream);
	write_video_header(stream);
	write_audio_header(stream);
}