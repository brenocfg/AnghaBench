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
struct mp_log {int dummy; } ;
struct mp_image {int dummy; } ;
struct image_writer_opts {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_PNG ; 
 struct image_writer_opts image_writer_opts_defaults ; 
 int /*<<< orphan*/  write_image (struct mp_image*,struct image_writer_opts*,char const*,int /*<<< orphan*/ *,struct mp_log*) ; 

void dump_png(struct mp_image *image, const char *filename, struct mp_log *log)
{
    struct image_writer_opts opts = image_writer_opts_defaults;
    opts.format = AV_CODEC_ID_PNG;
    write_image(image, &opts, filename, NULL, log);
}