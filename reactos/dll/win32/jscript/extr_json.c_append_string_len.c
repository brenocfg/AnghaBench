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
struct TYPE_3__ {size_t buf_size; size_t buf_len; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ stringify_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * heap_alloc (size_t) ; 
 int /*<<< orphan*/ * heap_realloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static BOOL append_string_len(stringify_ctx_t *ctx, const WCHAR *str, size_t len)
{
    if(!ctx->buf_size) {
        ctx->buf = heap_alloc(len*2*sizeof(WCHAR));
        if(!ctx->buf)
            return FALSE;
        ctx->buf_size = len*2;
    }else if(ctx->buf_len + len > ctx->buf_size) {
        WCHAR *new_buf;
        size_t new_size;

        new_size = ctx->buf_size * 2 + len;
        new_buf = heap_realloc(ctx->buf, new_size*sizeof(WCHAR));
        if(!new_buf)
            return FALSE;
        ctx->buf = new_buf;
        ctx->buf_size = new_size;
    }

    if(len)
        memcpy(ctx->buf + ctx->buf_len, str, len*sizeof(WCHAR));
    ctx->buf_len += len;
    return TRUE;
}