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
struct demux_internal {int /*<<< orphan*/  stream_base_filename; int /*<<< orphan*/  stream_size; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
#define  STREAM_CTRL_GET_BASE_FILENAME 129 
#define  STREAM_CTRL_GET_SIZE 128 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 char* talloc_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cached_stream_control(struct demux_internal *in, int cmd, void *arg)
{
    switch (cmd) {
    case STREAM_CTRL_GET_SIZE:
        if (in->stream_size < 0)
            return STREAM_UNSUPPORTED;
        *(int64_t *)arg = in->stream_size;
        return STREAM_OK;
    case STREAM_CTRL_GET_BASE_FILENAME:
        if (!in->stream_base_filename)
            return STREAM_UNSUPPORTED;
        *(char **)arg = talloc_strdup(NULL, in->stream_base_filename);
        return STREAM_OK;
    }
    return STREAM_ERROR;
}