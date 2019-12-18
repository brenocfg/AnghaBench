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
typedef  int /*<<< orphan*/  uint8_t ;
struct vo_wayland_state {int dnd_fd; scalar_t__ dnd_mime_score; int /*<<< orphan*/ * dnd_mime_type; int /*<<< orphan*/  dnd_offer; int /*<<< orphan*/  dnd_action; TYPE_1__* vo; } ;
struct pollfd {int member_0; int member_1; int revents; int /*<<< orphan*/  member_2; } ;
struct bstr {int dummy; } ;
typedef  size_t ptrdiff_t ;
struct TYPE_2__ {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_wayland_state*,char*,size_t) ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 struct bstr bstr0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  mp_event_drop_mime_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bstr,int /*<<< orphan*/ ) ; 
 scalar_t__ poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 size_t read (int,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/ * ta_realloc_size (struct vo_wayland_state*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * ta_zalloc_size (struct vo_wayland_state*,size_t const) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_data_offer_finish (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_dnd_fd(struct vo_wayland_state *wl)
{
    if (wl->dnd_fd == -1)
        return;

    struct pollfd fdp = { wl->dnd_fd, POLLIN | POLLERR | POLLHUP, 0 };
    if (poll(&fdp, 1, 0) <= 0)
        return;

    if (fdp.revents & POLLIN) {
        ptrdiff_t offset = 0;
        size_t data_read = 0;
        const size_t chunk_size = 1;
        uint8_t *buffer = ta_zalloc_size(wl, chunk_size);
        if (!buffer)
            goto end;

        while ((data_read = read(wl->dnd_fd, buffer + offset, chunk_size)) > 0) {
            offset += data_read;
            buffer = ta_realloc_size(wl, buffer, offset + chunk_size);
            memset(buffer + offset, 0, chunk_size);
            if (!buffer)
                goto end;
        }

        MP_VERBOSE(wl, "Read %td bytes from the DND fd\n", offset);

        struct bstr file_list = bstr0(buffer);
        mp_event_drop_mime_data(wl->vo->input_ctx, wl->dnd_mime_type,
                                file_list, wl->dnd_action);
        talloc_free(buffer);
end:
        wl_data_offer_finish(wl->dnd_offer);
        talloc_free(wl->dnd_mime_type);
        wl->dnd_mime_type = NULL;
        wl->dnd_mime_score = 0;
    }

    if (fdp.revents & (POLLIN | POLLERR | POLLHUP)) {
        close(wl->dnd_fd);
        wl->dnd_fd = -1;
    }
}