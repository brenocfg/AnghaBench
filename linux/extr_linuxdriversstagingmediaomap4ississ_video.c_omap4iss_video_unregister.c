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
struct iss_video {int /*<<< orphan*/  video; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void omap4iss_video_unregister(struct iss_video *video)
{
	video_unregister_device(&video->video);
}