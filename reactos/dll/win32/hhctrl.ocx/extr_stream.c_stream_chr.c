#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t p; size_t size; char* buf; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  strbuf_t ;
typedef  size_t ULONG ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ ,char*,int,size_t*) ; 
 int TRUE ; 
 int /*<<< orphan*/  strbuf_append (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static BOOL stream_chr(stream_t *stream, strbuf_t *buf, char c)
{
    BOOL b = TRUE;
    ULONG i;

    while(b) {
        for(i=stream->p; i<stream->size; i++) {
            if(stream->buf[i] == c) {
                b = FALSE;
                break;
            }
        }

        if(buf && i > stream->p)
            strbuf_append(buf, stream->buf+stream->p, i-stream->p);
        stream->p = i;

        if(stream->p == stream->size) {
            stream->p = 0;
            IStream_Read(stream->str, stream->buf, sizeof(stream->buf), &stream->size);
            if(!stream->size)
                break;
        }
    }

    return stream->size != 0;
}