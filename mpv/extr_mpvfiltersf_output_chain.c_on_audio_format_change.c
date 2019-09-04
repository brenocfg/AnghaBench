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
struct TYPE_4__ {int ao_needs_update; int /*<<< orphan*/  output_aformat; } ;
struct chain {int /*<<< orphan*/  f; int /*<<< orphan*/ * ao; TYPE_2__ public; TYPE_1__* convert_wrapper; } ;
struct TYPE_3__ {int /*<<< orphan*/  last_in_aformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_aframe_config_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_filter_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_audio_format_change(void *opaque)
{
    struct chain *p = opaque;

    // Let the f_output_chain user know what format to use. (Not quite proper,
    // since we overwrite what some other code normally automatically sets.
    // The main issue is that this callback is called before output_aformat can
    // be set, because we "block" the converter until the AO is reconfigured,
    // and mp_autoconvert_format_change_continue() is called.)
    mp_aframe_config_copy(p->public.output_aformat,
                          p->convert_wrapper->last_in_aformat);

    // Ask for calling mp_output_chain_set_ao().
    p->public.ao_needs_update = true;
    p->ao = NULL;

    // Do something silly to notify the f_output_chain user. (Not quite proper,
    // it's merely that this will cause the core to run again, and check the
    // flag set above.)
    mp_filter_wakeup(p->f);
}