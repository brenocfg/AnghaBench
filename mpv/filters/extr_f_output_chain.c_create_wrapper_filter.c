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
struct mp_user_filter {int last_is_active; int /*<<< orphan*/  last_in_aformat; struct chain* p; struct mp_filter* wrapper; } ;
struct mp_filter {struct mp_user_filter* priv; } ;
struct chain {int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  mp_aframe_create () ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_steal (struct mp_user_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_wrapper_filter ; 

__attribute__((used)) static struct mp_user_filter *create_wrapper_filter(struct chain *p)
{
    struct mp_filter *f = mp_filter_create(p->f, &user_wrapper_filter);
    if (!f)
        abort();
    struct mp_user_filter *wrapper = f->priv;
    wrapper->wrapper = f;
    wrapper->p = p;
    wrapper->last_in_aformat = talloc_steal(wrapper, mp_aframe_create());
    wrapper->last_is_active = true;
    mp_filter_add_pin(f, MP_PIN_IN, "in");
    mp_filter_add_pin(f, MP_PIN_OUT, "out");
    return wrapper;
}