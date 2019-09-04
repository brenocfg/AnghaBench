#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mp_user_filter {char* label; char* name; int failed; int error_eof_sent; double last_in_pts; double last_out_pts; scalar_t__ last_is_active; TYPE_2__* f; struct chain* p; } ;
struct mp_frame {int dummy; } ;
struct mp_filter_command {scalar_t__ is_active; int /*<<< orphan*/  type; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; struct mp_user_filter* priv; } ;
struct TYPE_6__ {int failed_output_conversion; } ;
struct chain {struct mp_user_filter* convert_wrapper; int /*<<< orphan*/  f; TYPE_1__ public; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 struct mp_frame MP_EOF_FRAME ; 
 int /*<<< orphan*/  MP_ERR (struct chain*,char*,char const*) ; 
 int /*<<< orphan*/  MP_FATAL (struct chain*,char*) ; 
 int /*<<< orphan*/  MP_FILTER_COMMAND_IS_ACTIVE ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct chain*,char*,char*,char*) ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  check_in_format_change (struct mp_user_filter*,struct mp_frame) ; 
 scalar_t__ mp_filter_command (TYPE_2__*,struct mp_filter_command*) ; 
 scalar_t__ mp_filter_has_failed (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_filter_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_filter_set_error_handler (TYPE_2__*,struct mp_filter*) ; 
 int /*<<< orphan*/  mp_filter_wakeup (int /*<<< orphan*/ ) ; 
 double mp_frame_get_pts (struct mp_frame) ; 
 scalar_t__ mp_pin_can_transfer_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_pin_in_needs_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,struct mp_frame) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_transfer_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_user(struct mp_filter *f)
{
    struct mp_user_filter *u = f->priv;
    struct chain *p = u->p;

    mp_filter_set_error_handler(u->f, f);
    const char *name = u->label ? u->label : u->name;
    assert(u->name);

    if (!u->failed && mp_filter_has_failed(u->f)) {
        if (u == p->convert_wrapper) {
            // This is a fuckup we can't ignore.
            MP_FATAL(p, "Cannot convert decoder/filter output to any format "
                     "supported by the output.\n");
            p->public.failed_output_conversion = true;
            mp_filter_wakeup(p->f);
        } else {
            MP_ERR(p, "Disabling filter %s because it has failed.\n", name);
            mp_filter_reset(u->f); // clear out staled buffered data
        }
        u->failed = true;
    }

    if (u->failed) {
        if (u == p->convert_wrapper) {
            if (mp_pin_in_needs_data(f->ppins[1])) {
                if (!u->error_eof_sent)
                    mp_pin_in_write(f->ppins[1], MP_EOF_FRAME);
                u->error_eof_sent = true;
            }
            return;
        }

        mp_pin_transfer_data(f->ppins[1], f->ppins[0]);
        return;
    }

    if (mp_pin_can_transfer_data(u->f->pins[0], f->ppins[0])) {
        struct mp_frame frame = mp_pin_out_read(f->ppins[0]);

        check_in_format_change(u, frame);

        double pts = mp_frame_get_pts(frame);
        if (pts != MP_NOPTS_VALUE)
            u->last_in_pts = pts;

        mp_pin_in_write(u->f->pins[0], frame);
    }

    if (mp_pin_can_transfer_data(f->ppins[1], u->f->pins[1])) {
        struct mp_frame frame = mp_pin_out_read(u->f->pins[1]);

        double pts = mp_frame_get_pts(frame);
        if (pts != MP_NOPTS_VALUE)
            u->last_out_pts = pts;

        mp_pin_in_write(f->ppins[1], frame);

        struct mp_filter_command cmd = {.type = MP_FILTER_COMMAND_IS_ACTIVE};
        if (mp_filter_command(u->f, &cmd) && u->last_is_active != cmd.is_active) {
            u->last_is_active = cmd.is_active;
            MP_VERBOSE(p, "[%s] (%sabled)\n", u->name,
                       u->last_is_active ? "en" : "dis");
        }
    }
}