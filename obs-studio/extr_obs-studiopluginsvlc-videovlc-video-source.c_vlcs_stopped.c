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
struct vlc_source {int /*<<< orphan*/  source; int /*<<< orphan*/  loop; } ;
struct libvlc_event_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (struct libvlc_event_t const*) ; 
 int /*<<< orphan*/  obs_source_output_video (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlcs_stopped(const struct libvlc_event_t *event, void *data)
{
	struct vlc_source *c = data;
	if (!c->loop)
		obs_source_output_video(c->source, NULL);

	UNUSED_PARAMETER(event);
}