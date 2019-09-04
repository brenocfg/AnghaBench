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
struct sd_ass_priv {int /*<<< orphan*/  ass_library; } ;
struct sd {int /*<<< orphan*/  log; TYPE_1__* attachments; struct mp_subtitle_opts* opts; struct sd_ass_priv* priv; } ;
struct mp_subtitle_opts {int /*<<< orphan*/  use_embedded_fonts; int /*<<< orphan*/  ass_enabled; } ;
struct demux_attachment {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int num_entries; struct demux_attachment* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ass_add_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ attachment_is_font (int /*<<< orphan*/ ,struct demux_attachment*) ; 

__attribute__((used)) static void add_subtitle_fonts(struct sd *sd)
{
    struct sd_ass_priv *ctx = sd->priv;
    struct mp_subtitle_opts *opts = sd->opts;
    if (!opts->ass_enabled || !opts->use_embedded_fonts || !sd->attachments)
        return;
    for (int i = 0; i < sd->attachments->num_entries; i++) {
        struct demux_attachment *f = &sd->attachments->entries[i];
        if (attachment_is_font(sd->log, f))
            ass_add_font(ctx->ass_library, f->name, f->data, f->data_size);
    }
}