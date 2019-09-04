#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pos; scalar_t__ (* seek ) (TYPE_1__*,scalar_t__) ;int /*<<< orphan*/  cancel; int /*<<< orphan*/  seekable; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  MP_MSG (TYPE_1__*,int,char*) ; 
 int MSGL_ERR ; 
 int MSGL_V ; 
 scalar_t__ mp_cancel_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_drop_buffers (TYPE_1__*) ; 
 scalar_t__ stub1 (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static bool stream_seek_unbuffered(stream_t *s, int64_t newpos)
{
    if (newpos != s->pos) {
        if (newpos > s->pos && !s->seekable) {
            MP_ERR(s, "Cannot seek forward in this stream\n");
            return false;
        }
        if (newpos < s->pos && !s->seekable) {
            MP_ERR(s, "Cannot seek backward in linear streams!\n");
            return false;
        }
        if (s->seek(s, newpos) <= 0) {
            int level = mp_cancel_test(s->cancel) ? MSGL_V : MSGL_ERR;
            MP_MSG(s, level, "Seek failed\n");
            return false;
        }
        stream_drop_buffers(s);
        s->pos = newpos;
    }
    return true;
}