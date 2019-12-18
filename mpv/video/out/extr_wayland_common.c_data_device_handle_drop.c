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
struct wl_data_device {int dummy; } ;
struct vo_wayland_state {int dnd_fd; int /*<<< orphan*/  dnd_mime_type; int /*<<< orphan*/  dnd_offer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo_wayland_state*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo_wayland_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 int pipe2 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_data_offer_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void data_device_handle_drop(void *data, struct wl_data_device *wl_ddev)
{
    struct vo_wayland_state *wl = data;

    int pipefd[2];

    if (pipe2(pipefd, O_CLOEXEC) == -1) {
        MP_ERR(wl, "Failed to create dnd pipe!\n");
        return;
    }

    MP_VERBOSE(wl, "Receiving DND offer with mime %s\n", wl->dnd_mime_type);

    wl_data_offer_receive(wl->dnd_offer, wl->dnd_mime_type, pipefd[1]);
    close(pipefd[1]);

    wl->dnd_fd = pipefd[0];
}