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
struct mp_swresample {struct mp_filter* f; } ;
struct mp_filter {int dummy; } ;
struct TYPE_2__ {scalar_t__ normalize; } ;
struct af_resample {scalar_t__ global_normalize; TYPE_1__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  abort () ; 
 struct mp_swresample* mp_swresample_create (struct mp_filter*,TYPE_1__*) ; 
 int /*<<< orphan*/  talloc_free (struct af_resample*) ; 

__attribute__((used)) static struct mp_filter *af_lavrresample_create(struct mp_filter *parent,
                                                void *options)
{
    struct af_resample *s = options;

    if (s->opts.normalize < 0)
        s->opts.normalize = s->global_normalize;

    struct mp_swresample *swr = mp_swresample_create(parent, &s->opts);
    if (!swr)
        abort();

    MP_WARN(swr->f, "This filter is deprecated! Use the --audio-resample- options"
            " to customize resampling, or the --af=aresample filter.\n");

    talloc_free(s);
    return swr->f;
}