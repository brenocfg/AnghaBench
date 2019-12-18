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
struct obs_x264 {int /*<<< orphan*/ * extra_data; int /*<<< orphan*/ * sei; int /*<<< orphan*/ * context; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x264_encoder_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_data(struct obs_x264 *obsx264)
{
	if (obsx264->context) {
		x264_encoder_close(obsx264->context);
		bfree(obsx264->sei);
		bfree(obsx264->extra_data);

		obsx264->context = NULL;
		obsx264->sei = NULL;
		obsx264->extra_data = NULL;
	}
}