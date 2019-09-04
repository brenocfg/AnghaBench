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
struct vo_wayland_output {struct vo_wayland_output* model; struct vo_wayland_output* make; int /*<<< orphan*/  link; int /*<<< orphan*/  id; int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ ,char*,struct vo_wayland_output*,struct vo_wayland_output*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct vo_wayland_output*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_output(struct vo_wayland_output *out)
{
    if (!out)
        return;

    MP_VERBOSE(out->wl, "Deregistering output %s %s (0x%x)\n", out->make,
               out->model, out->id);
    wl_list_remove(&out->link);
    talloc_free(out->make);
    talloc_free(out->model);
    talloc_free(out);
    return;
}