#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct options {int /*<<< orphan*/  test_crypto; } ;
struct TYPE_6__ {int /*<<< orphan*/  packet_id; } ;
struct TYPE_5__ {TYPE_3__ crypto_options; int /*<<< orphan*/  frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  ks; } ;
struct context {TYPE_2__ c2; TYPE_1__ c1; struct options options; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVM_LEVEL_1 ; 
 int /*<<< orphan*/  context_gc_free (struct context*) ; 
 int /*<<< orphan*/  context_init_1 (struct context*) ; 
 int /*<<< orphan*/  do_init_crypto_static (struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_finalize_options (struct context*,struct options const*) ; 
 int /*<<< orphan*/  init_verb_mute (struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_schedule_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  next_connection_entry (struct context*) ; 
 int /*<<< orphan*/  packet_id_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_crypto (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
test_crypto_thread(void *arg)
{
    struct context *c = (struct context *) arg;
    const struct options *options = &c->options;

    ASSERT(options->test_crypto);
    init_verb_mute(c, IVM_LEVEL_1);
    context_init_1(c);
    next_connection_entry(c);
    do_init_crypto_static(c, 0);

    frame_finalize_options(c, options);

    test_crypto(&c->c2.crypto_options, &c->c2.frame);

    key_schedule_free(&c->c1.ks, true);
    packet_id_free(&c->c2.crypto_options.packet_id);

    context_gc_free(c);
    return NULL;
}