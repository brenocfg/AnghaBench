#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_lavfi {int dummy; } ;
struct lavfi_pad {int pin_index; scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  dir; int /*<<< orphan*/  pin; } ;
struct lavfi {int num_in_pads; int num_out_pads; scalar_t__ force_type; TYPE_1__* f; struct mp_lavfi public; scalar_t__ force_bidir; struct lavfi_pad** out_pads; struct lavfi_pad** in_pads; scalar_t__ failed; } ;
struct TYPE_3__ {int num_pins; int /*<<< orphan*/ * ppins; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct lavfi*,char*) ; 
 scalar_t__ MP_PIN_IN ; 
 scalar_t__ MP_PIN_OUT ; 
 int /*<<< orphan*/  mp_filter_add_pin (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_pin_get_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  precreate_graph (struct lavfi*,int) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

__attribute__((used)) static struct mp_lavfi *do_init(struct lavfi *c)
{
    precreate_graph(c, true);

    if (c->failed)
        goto error;

    for (int n = 0; n < c->num_in_pads + c->num_out_pads; n++) {
        // First add input pins to satisfy order for bidir graph types.
        struct lavfi_pad *pad =
            n < c->num_in_pads ? c->in_pads[n] : c->out_pads[n - c->num_in_pads];

        pad->pin_index = c->f->num_pins;
        pad->pin = mp_filter_add_pin(c->f, pad->dir, pad->name);

        if (c->force_type && c->force_type != pad->type) {
            MP_FATAL(c, "mismatching media type\n");
            goto error;
        }
    }

    if (c->force_bidir) {
        if (c->f->num_pins != 2) {
            MP_FATAL(c, "exactly 2 pads required\n");
            goto error;
        }
        if (mp_pin_get_dir(c->f->ppins[0]) != MP_PIN_OUT ||
            mp_pin_get_dir(c->f->ppins[1]) != MP_PIN_IN)
        {
            MP_FATAL(c, "1 input and 1 output pad required\n");
            goto error;
        }
    }

    return &c->public;

error:
    talloc_free(c->f);
    return NULL;
}