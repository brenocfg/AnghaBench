#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stream {int dummy; } ;
struct encoder_context {TYPE_2__* encoder; int /*<<< orphan*/  twopass_bytebuffer; int /*<<< orphan*/  global; int /*<<< orphan*/  type; TYPE_1__* options; } ;
struct bstr {scalar_t__ start; } ;
struct TYPE_4__ {int flags; scalar_t__ stats_in; } ;
struct TYPE_3__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int AV_CODEC_FLAG_PASS1 ; 
 int AV_CODEC_FLAG_PASS2 ; 
 int /*<<< orphan*/  MP_INFO (struct encoder_context*,char*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct encoder_context*,char*,char*) ; 
 int /*<<< orphan*/  free_stream (struct stream*) ; 
 int /*<<< orphan*/  open_output_stream (char*,int /*<<< orphan*/ ) ; 
 struct stream* stream_open (char*,int /*<<< orphan*/ ) ; 
 struct bstr stream_read_complete (struct stream*,struct encoder_context*,int) ; 
 int /*<<< orphan*/  stream_type_name (int /*<<< orphan*/ ) ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static void encoder_2pass_prepare(struct encoder_context *p)
{
    char *filename = talloc_asprintf(NULL, "%s-%s-pass1.log",
                                     p->options->file,
                                     stream_type_name(p->type));

    if (p->encoder->flags & AV_CODEC_FLAG_PASS2) {
        MP_INFO(p, "Reading 2-pass log: %s\n", filename);
        struct stream *s = stream_open(filename, p->global);
        if (s) {
            struct bstr content = stream_read_complete(s, p, 1000000000);
            if (content.start) {
                p->encoder->stats_in = content.start;
            } else {
                MP_WARN(p, "could not read '%s', "
                        "disabling 2-pass encoding at pass 1\n", filename);
            }
            free_stream(s);
        } else {
            MP_WARN(p, "could not open '%s', "
                    "disabling 2-pass encoding at pass 2\n", filename);
            p->encoder->flags &= ~(unsigned)AV_CODEC_FLAG_PASS2;
        }
    }

    if (p->encoder->flags & AV_CODEC_FLAG_PASS1) {
        MP_INFO(p, "Writing to 2-pass log: %s\n", filename);
        p->twopass_bytebuffer = open_output_stream(filename, p->global);
        if (!p->twopass_bytebuffer) {
            MP_WARN(p, "could not open '%s', "
                    "disabling 2-pass encoding at pass 1\n", filename);
            p->encoder->flags &= ~(unsigned)AV_CODEC_FLAG_PASS1;
        }
    }

    talloc_free(filename);
}