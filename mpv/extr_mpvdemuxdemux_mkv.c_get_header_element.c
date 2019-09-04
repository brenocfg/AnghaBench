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
typedef  scalar_t__ uint32_t ;
struct mkv_demuxer {int num_headers; struct header_elem* headers; } ;
struct header_elem {scalar_t__ id; scalar_t__ pos; } ;
struct demuxer {struct mkv_demuxer* priv; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ MATROSKA_ID_CLUSTER ; 
 scalar_t__ MATROSKA_ID_SEEKHEAD ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct mkv_demuxer*,struct header_elem*,int,struct header_elem) ; 
 int /*<<< orphan*/  ebml_is_mkv_level1_id (scalar_t__) ; 

__attribute__((used)) static struct header_elem *get_header_element(struct demuxer *demuxer,
                                              uint32_t id,
                                              int64_t element_filepos)
{
    struct mkv_demuxer *mkv_d = demuxer->priv;

    // Note that some files in fact contain a SEEKHEAD with a list of all
    // clusters - we have no use for that.
    if (!ebml_is_mkv_level1_id(id) || id == MATROSKA_ID_CLUSTER)
        return NULL;

    for (int n = 0; n < mkv_d->num_headers; n++) {
        struct header_elem *elem = &mkv_d->headers[n];
        // SEEKHEAD is the only element that can happen multiple times.
        // Other elements might be duplicated (or attempted to be read twice,
        // even if it's only once in the file), but only the first is used.
        if (elem->id == id && (id != MATROSKA_ID_SEEKHEAD ||
                               elem->pos == element_filepos))
            return elem;
    }
    struct header_elem elem = { .id = id, .pos = element_filepos };
    MP_TARRAY_APPEND(mkv_d, mkv_d->headers, mkv_d->num_headers, elem);
    return &mkv_d->headers[mkv_d->num_headers - 1];
}