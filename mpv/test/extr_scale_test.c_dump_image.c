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
struct scale_test {TYPE_1__* ctx; } ;
struct mp_image {int dummy; } ;
struct image_writer_opts {int /*<<< orphan*/  format; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; int /*<<< orphan*/  global; int /*<<< orphan*/  out_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_PNG ; 
 int /*<<< orphan*/  MP_FATAL (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  abort () ; 
 struct image_writer_opts image_writer_opts_defaults ; 
 char* mp_tprintf (int,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  write_image (struct mp_image*,struct image_writer_opts*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_image(struct scale_test *stest, const char *name,
                       struct mp_image *img)
{
    char *path = mp_tprintf(4096, "%s/%s.png", stest->ctx->out_path, name);

    struct image_writer_opts opts = image_writer_opts_defaults;
    opts.format = AV_CODEC_ID_PNG;

    if (!write_image(img, &opts, path, stest->ctx->global, stest->ctx->log)) {
        MP_FATAL(stest->ctx, "Failed to write '%s'.\n", path);
        abort();
    }
}