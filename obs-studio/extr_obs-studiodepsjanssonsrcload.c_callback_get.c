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
struct TYPE_2__ {size_t pos; size_t len; size_t (* callback ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;char* data; int /*<<< orphan*/  arg; } ;
typedef  TYPE_1__ callback_data_t ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  MAX_BUF_LEN ; 
 size_t stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int callback_get(void *data)
{
    char c;
    callback_data_t *stream = data;

    if(stream->pos >= stream->len) {
        stream->pos = 0;
        stream->len = stream->callback(stream->data, MAX_BUF_LEN, stream->arg);
        if(stream->len == 0 || stream->len == (size_t)-1)
            return EOF;
    }

    c = stream->data[stream->pos];
    stream->pos++;
    return (unsigned char)c;
}