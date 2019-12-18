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
struct test_ctx {int /*<<< orphan*/  out_path; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct test_ctx*,char*,char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* mp_tprintf (int,char*,int /*<<< orphan*/ ,char const*) ; 

FILE *test_open_out(struct test_ctx *ctx, const char *name)
{
    char *path = mp_tprintf(4096, "%s/%s", ctx->out_path, name);
    FILE *f = fopen(path, "wb");
    if (!f) {
        MP_FATAL(ctx, "Could not open '%s' for writing.\n", path);
        abort();
    }
    return f;
}