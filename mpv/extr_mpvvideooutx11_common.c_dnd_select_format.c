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
struct vo_x11_state {scalar_t__ dnd_requested_format; } ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_x11_state*,char*,char*) ; 
 scalar_t__ dnd_format_is_better (struct vo_x11_state*,scalar_t__,scalar_t__) ; 
 char* x11_atom_name (struct vo_x11_state*,scalar_t__) ; 

__attribute__((used)) static void dnd_select_format(struct vo_x11_state *x11, Atom *args, int items)
{
    x11->dnd_requested_format = 0;

    for (int n = 0; n < items; n++) {
        MP_VERBOSE(x11, "DnD type: '%s'\n", x11_atom_name(x11, args[n]));
        // There are other types; possibly not worth supporting.
        if (dnd_format_is_better(x11, x11->dnd_requested_format, args[n]))
            x11->dnd_requested_format = args[n];
    }

    MP_VERBOSE(x11, "Selected DnD type: %s\n", x11->dnd_requested_format ?
                    x11_atom_name(x11, x11->dnd_requested_format) : "(none)");
}