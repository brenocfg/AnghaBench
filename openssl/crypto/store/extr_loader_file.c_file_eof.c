#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  file; int /*<<< orphan*/  last_handler_ctx; TYPE_2__* last_handler; } ;
struct TYPE_7__ {int end_reached; } ;
struct TYPE_9__ {TYPE_4__ file; TYPE_1__ dir; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_3__ _; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* eof ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ OSSL_STORE_LOADER_CTX ;

/* Variables and functions */
 int BIO_eof (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dir ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int file_eof(OSSL_STORE_LOADER_CTX *ctx)
{
    if (ctx->type == is_dir)
        return ctx->_.dir.end_reached;

    if (ctx->_.file.last_handler != NULL
        && !ctx->_.file.last_handler->eof(ctx->_.file.last_handler_ctx))
        return 0;
    return BIO_eof(ctx->_.file.file);
}