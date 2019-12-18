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
typedef  int /*<<< orphan*/  http_request_t ;
typedef  int /*<<< orphan*/  data_stream_t ;
struct TYPE_2__ {int state; } ;
typedef  TYPE_1__ chunked_stream_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CHUNKED_STREAM_STATE_DISCARD_EOL_AT_END 130 
#define  CHUNKED_STREAM_STATE_END_OF_STREAM 129 
#define  CHUNKED_STREAM_STATE_ERROR 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL chunked_end_of_data(data_stream_t *stream, http_request_t *req)
{
    chunked_stream_t *chunked_stream = (chunked_stream_t*)stream;
    switch(chunked_stream->state) {
    case CHUNKED_STREAM_STATE_DISCARD_EOL_AT_END:
    case CHUNKED_STREAM_STATE_END_OF_STREAM:
    case CHUNKED_STREAM_STATE_ERROR:
        return TRUE;
    default:
        return FALSE;
    }
}