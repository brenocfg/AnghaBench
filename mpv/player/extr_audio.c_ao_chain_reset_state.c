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
struct ao_chain {int out_eof; int underrun; int /*<<< orphan*/  ao_buffer; int /*<<< orphan*/  output_frame; int /*<<< orphan*/  last_out_pts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_audio_buffer_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ao_chain_reset_state(struct ao_chain *ao_c)
{
    ao_c->last_out_pts = MP_NOPTS_VALUE;
    TA_FREEP(&ao_c->output_frame);
    ao_c->out_eof = false;
    ao_c->underrun = false;

    mp_audio_buffer_clear(ao_c->ao_buffer);
}