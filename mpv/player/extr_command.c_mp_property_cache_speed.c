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
typedef  int /*<<< orphan*/  uint64_t ;
struct m_property {int dummy; } ;
struct demux_reader_state {int /*<<< orphan*/  bytes_per_second; } ;
struct TYPE_2__ {int /*<<< orphan*/  demuxer; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
 int M_PROPERTY_PRINT ; 
 int M_PROPERTY_UNAVAILABLE ; 
 int /*<<< orphan*/  demux_get_reader_state (int /*<<< orphan*/ ,struct demux_reader_state*) ; 
 int /*<<< orphan*/  format_file_size (int /*<<< orphan*/ ) ; 
 int m_property_int64_ro (int,void*,int /*<<< orphan*/ ) ; 
 char* talloc_strdup_append (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mp_property_cache_speed(void *ctx, struct m_property *prop,
                                   int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (!mpctx->demuxer)
        return M_PROPERTY_UNAVAILABLE;

    struct demux_reader_state s;
    demux_get_reader_state(mpctx->demuxer, &s);

    uint64_t val = s.bytes_per_second;

    if (action == M_PROPERTY_PRINT) {
        *(char **)arg = talloc_strdup_append(format_file_size(val), "/s");
        return M_PROPERTY_OK;
    }
    return m_property_int64_ro(action, arg, val);
}