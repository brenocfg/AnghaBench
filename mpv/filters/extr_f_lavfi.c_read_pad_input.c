#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct lavfi_pad {scalar_t__ dir; scalar_t__ type; int /*<<< orphan*/  name; TYPE_5__ in_fmt; TYPE_1__ pending; int /*<<< orphan*/  pin; } ;
struct lavfi {int draining_recover; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct lavfi*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MP_FRAME_EOF ; 
 scalar_t__ MP_PIN_IN ; 
 int /*<<< orphan*/  MP_VERBOSE (struct lavfi*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  is_format_ok (TYPE_1__,TYPE_5__) ; 
 scalar_t__ mp_frame_is_data (TYPE_1__) ; 
 int /*<<< orphan*/  mp_frame_type_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_frame_unref (TYPE_1__*) ; 
 TYPE_1__ mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_global_eof (struct lavfi*) ; 

__attribute__((used)) static void read_pad_input(struct lavfi *c, struct lavfi_pad *pad)
{
    assert(pad->dir == MP_PIN_IN);

    if (pad->pending.type || c->draining_recover)
        return;

    pad->pending = mp_pin_out_read(pad->pin);

    if (pad->pending.type && pad->pending.type != MP_FRAME_EOF &&
        pad->pending.type != pad->type)
    {
        MP_FATAL(c, "unknown frame %s\n", mp_frame_type_str(pad->pending.type));
        mp_frame_unref(&pad->pending);
    }

    if (mp_frame_is_data(pad->pending) && pad->in_fmt.type &&
        !is_format_ok(pad->pending, pad->in_fmt))
    {
        if (!c->draining_recover)
            MP_VERBOSE(c, "format change on %s\n", pad->name);
        c->draining_recover = true;
        if (c->initialized)
            send_global_eof(c);
    }
}