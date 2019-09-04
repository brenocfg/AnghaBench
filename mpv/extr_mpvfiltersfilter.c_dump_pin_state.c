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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct mp_pin {scalar_t__ dir; TYPE_1__ data; scalar_t__ data_requested; scalar_t__ within_conn; int /*<<< orphan*/  manual_connection; TYPE_3__* conn; TYPE_2__* user_conn; int /*<<< orphan*/  name; } ;
struct mp_filter {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  owner; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ MP_PIN_IN ; 
 int /*<<< orphan*/  MP_WARN (struct mp_filter*,char*,struct mp_pin*,int /*<<< orphan*/ ,char*,char*,TYPE_2__*,char*,TYPE_3__*,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 char* filt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_frame_type_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_pin_state(struct mp_filter *f, struct mp_pin *pin)
{
    MP_WARN(f, "  [%p] %s %s c=%s[%p] f=%s[%p] m=%s[%p] %s %s %s\n",
        pin, pin->name, pin->dir == MP_PIN_IN ? "->" : "<-",
        pin->user_conn ? filt_name(pin->user_conn->owner) : "-", pin->user_conn,
        pin->conn ? filt_name(pin->conn->owner) : "-", pin->conn,
        filt_name(pin->manual_connection), pin->manual_connection,
        pin->within_conn ? "(within)" : "",
        pin->data_requested ? "(request)" : "",
        mp_frame_type_str(pin->data.type));
}