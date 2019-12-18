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
struct wl_data_offer {int dummy; } ;
struct vo_wayland_state {int dnd_mime_score; int /*<<< orphan*/  dnd_mime_type; TYPE_1__* vo; } ;
struct TYPE_2__ {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_wayland_state*,char*,int /*<<< orphan*/ ) ; 
 int mp_event_get_mime_type_score (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_strdup (struct vo_wayland_state*,char const*) ; 

__attribute__((used)) static void data_offer_handle_offer(void *data, struct wl_data_offer *offer,
                                    const char *mime_type)
{
    struct vo_wayland_state *wl = data;
    int score = mp_event_get_mime_type_score(wl->vo->input_ctx, mime_type);
    if (score > wl->dnd_mime_score) {
        wl->dnd_mime_score = score;
        talloc_free(wl->dnd_mime_type);
        wl->dnd_mime_type = talloc_strdup(wl, mime_type);
        MP_VERBOSE(wl, "Given DND offer with mime type %s\n", wl->dnd_mime_type);
    }
}