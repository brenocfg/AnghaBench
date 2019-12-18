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
struct mp_user_filter {char* name; int /*<<< orphan*/  f; int /*<<< orphan*/  wrapper; } ;
struct chain {int /*<<< orphan*/  num_post_filters; int /*<<< orphan*/  post_filters; int /*<<< orphan*/  frame_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FRAME_AUDIO ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_user_filter*) ; 
 int /*<<< orphan*/  abort () ; 
 struct mp_user_filter* create_wrapper_filter (struct chain*) ; 
 int /*<<< orphan*/  mp_autoaspeed_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_audio_things(struct chain *p)
{
    p->frame_type = MP_FRAME_AUDIO;

    struct mp_user_filter *f = create_wrapper_filter(p);
    f->name = "userspeed";
    f->f = mp_autoaspeed_create(f->wrapper);
    if (!f->f)
        abort();
    MP_TARRAY_APPEND(p, p->post_filters, p->num_post_filters, f);
}