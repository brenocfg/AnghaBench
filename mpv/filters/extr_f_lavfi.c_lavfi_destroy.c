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
struct mp_filter {struct lavfi* priv; } ;
struct lavfi {int /*<<< orphan*/  tmp_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lavfi_reset (struct mp_filter*) ; 

__attribute__((used)) static void lavfi_destroy(struct mp_filter *f)
{
    struct lavfi *c = f->priv;

    lavfi_reset(f);
    av_frame_free(&c->tmp_frame);
}