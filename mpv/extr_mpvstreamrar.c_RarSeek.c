#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ real_size; int chunk_count; scalar_t__ s; int /*<<< orphan*/  global; int /*<<< orphan*/  cancel; TYPE_2__* current_chunk; scalar_t__ i_pos; TYPE_2__** chunk; } ;
typedef  TYPE_1__ rar_file_t ;
struct TYPE_5__ {scalar_t__ cummulated_size; scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/  mrl; } ;
typedef  TYPE_2__ rar_file_chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_READ ; 
 int /*<<< orphan*/  free_stream (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stream_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stream_seek (scalar_t__,scalar_t__ const) ; 

int  RarSeek(rar_file_t *file, uint64_t position)
{
    if (position > file->real_size)
        position = file->real_size;

    /* Search the chunk */
    const rar_file_chunk_t *old_chunk = file->current_chunk;
    for (int i = 0; i < file->chunk_count; i++) {
        file->current_chunk = file->chunk[i];
        if (position < file->current_chunk->cummulated_size + file->current_chunk->size)
            break;
    }
    file->i_pos = position;

    const uint64_t offset = file->current_chunk->offset +
                            (position - file->current_chunk->cummulated_size);

    if (strcmp(old_chunk->mrl, file->current_chunk->mrl)) {
        if (file->s)
            free_stream(file->s);
        file->s = stream_create(file->current_chunk->mrl, STREAM_READ,
                                file->cancel, file->global);
    }
    return file->s ? stream_seek(file->s, offset) : 0;
}