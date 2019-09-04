#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct stream {int dummy; } ;
struct TYPE_10__ {char* path; int seekable; int /*<<< orphan*/  control; int /*<<< orphan*/  close; int /*<<< orphan*/  seek; int /*<<< orphan*/  fill_buffer; TYPE_2__* priv; int /*<<< orphan*/  global; int /*<<< orphan*/  cancel; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_11__ {int /*<<< orphan*/  global; int /*<<< orphan*/  cancel; struct stream* s; TYPE_3__* current_chunk; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ rar_file_t ;
struct TYPE_12__ {char* mrl; } ;
typedef  TYPE_3__ rar_file_chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  RarFileDelete (TYPE_2__*) ; 
 scalar_t__ RarParse (struct stream*,int*,TYPE_2__***) ; 
 scalar_t__ RarProbe (struct stream*) ; 
 int /*<<< orphan*/  RarSeek (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
 int STREAM_READ ; 
 int STREAM_SAFE_ONLY ; 
 int /*<<< orphan*/  free_stream (struct stream*) ; 
 int /*<<< orphan*/  mp_url_unescape_inplace (char*) ; 
 int /*<<< orphan*/  rar_entry_close ; 
 int /*<<< orphan*/  rar_entry_control ; 
 int /*<<< orphan*/  rar_entry_fill_buffer ; 
 int /*<<< orphan*/  rar_entry_seek ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct stream* stream_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (TYPE_2__**) ; 
 char* talloc_strdup (TYPE_1__*,char*) ; 

__attribute__((used)) static int rar_entry_open(stream_t *stream)
{
    if (!strchr(stream->path, '|'))
        return STREAM_ERROR;

    char *base = talloc_strdup(stream, stream->path);
    char *name = strchr(base, '|');
    *name++ = '\0';
    mp_url_unescape_inplace(base);

    struct stream *rar = stream_create(base, STREAM_READ | STREAM_SAFE_ONLY,
                                       stream->cancel, stream->global);
    if (!rar)
        return STREAM_ERROR;

    int count;
    rar_file_t **files;
    if (RarProbe(rar) || RarParse(rar, &count, &files)) {
        free_stream(rar);
        return STREAM_ERROR;
    }

    rar_file_t *file = NULL;
    for (int i = 0; i < count; i++) {
        if (!file && strcmp(files[i]->name, name) == 0)
            file = files[i];
        else
            RarFileDelete(files[i]);
    }
    talloc_free(files);
    if (!file) {
        free_stream(rar);
        return STREAM_ERROR;
    }

    rar_file_chunk_t dummy = {
        .mrl = base,
    };
    file->current_chunk = &dummy;
    file->s = rar; // transfer ownership
    file->cancel = stream->cancel;
    file->global = stream->global;
    RarSeek(file, 0);

    stream->priv = file;
    stream->fill_buffer = rar_entry_fill_buffer;
    stream->seek = rar_entry_seek;
    stream->seekable = true;
    stream->close = rar_entry_close;
    stream->control = rar_entry_control;

    return STREAM_OK;
}