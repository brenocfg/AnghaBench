#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vo_x11_state {int /*<<< orphan*/  parent; int /*<<< orphan*/  window; } ;
struct vo {struct vo_x11_state* x11; } ;
struct TYPE_4__ {long* l; } ;
struct TYPE_5__ {scalar_t__ message_type; TYPE_1__ data; } ;
typedef  TYPE_2__ XClientMessageEvent ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_x11_state*,char*) ; 
 scalar_t__ XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 long XEMBED_EMBEDDED_NOTIFY ; 
 int /*<<< orphan*/  _XEMBED ; 

__attribute__((used)) static void vo_x11_xembed_handle_message(struct vo *vo, XClientMessageEvent *ce)
{
    struct vo_x11_state *x11 = vo->x11;
    if (!x11->window || !x11->parent || ce->message_type != XA(x11, _XEMBED))
        return;

    long msg = ce->data.l[1];
    if (msg == XEMBED_EMBEDDED_NOTIFY)
        MP_VERBOSE(x11, "Parent windows supports XEmbed.\n");
}