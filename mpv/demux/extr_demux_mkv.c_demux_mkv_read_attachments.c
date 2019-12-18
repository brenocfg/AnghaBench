#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ebml_parse_ctx {int /*<<< orphan*/  talloc_ctx; int /*<<< orphan*/  member_0; } ;
struct ebml_attachments {int n_attached_file; struct ebml_attached_file* attached_file; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
struct ebml_attached_file {char* file_name; char* file_mime_type; TYPE_1__ file_data; int /*<<< orphan*/  n_file_data; } ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  demuxer_add_attachment (TYPE_2__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebml_attachments_desc ; 
 scalar_t__ ebml_read_element (int /*<<< orphan*/ *,struct ebml_parse_ctx*,struct ebml_attachments*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int demux_mkv_read_attachments(demuxer_t *demuxer)
{
    stream_t *s = demuxer->stream;

    MP_DBG(demuxer, "Parsing attachments...\n");

    struct ebml_attachments attachments = {0};
    struct ebml_parse_ctx parse_ctx = {demuxer->log};
    if (ebml_read_element(s, &parse_ctx, &attachments,
                          &ebml_attachments_desc) < 0)
        return -1;

    for (int i = 0; i < attachments.n_attached_file; i++) {
        struct ebml_attached_file *attachment = &attachments.attached_file[i];
        if (!attachment->file_name || !attachment->file_mime_type
            || !attachment->n_file_data) {
            MP_WARN(demuxer, "Malformed attachment\n");
            continue;
        }
        char *name = attachment->file_name;
        char *mime = attachment->file_mime_type;
        demuxer_add_attachment(demuxer, name, mime, attachment->file_data.start,
                               attachment->file_data.len);
        MP_DBG(demuxer, "Attachment: %s, %s, %zu bytes\n",
               name, mime, attachment->file_data.len);
    }

    talloc_free(parse_ctx.talloc_ctx);
    return 0;
}