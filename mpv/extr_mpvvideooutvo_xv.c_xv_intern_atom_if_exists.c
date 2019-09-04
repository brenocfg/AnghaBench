#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xvctx {int /*<<< orphan*/  xv_port; } ;
struct vo {TYPE_1__* x11; struct xvctx* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ XvAttribute ;
struct TYPE_5__ {int /*<<< orphan*/  display; } ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  XFree (TYPE_2__*) ; 
 int /*<<< orphan*/  XInternAtom (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* XvQueryPortAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static Atom xv_intern_atom_if_exists(struct vo *vo, char const *atom_name)
{
    struct xvctx *ctx = vo->priv;
    XvAttribute *attributes;
    int attrib_count, i;
    Atom xv_atom = None;

    attributes = XvQueryPortAttributes(vo->x11->display, ctx->xv_port,
                                       &attrib_count);
    if (attributes != NULL) {
        for (i = 0; i < attrib_count; ++i) {
            if (strcmp(attributes[i].name, atom_name) == 0) {
                xv_atom = XInternAtom(vo->x11->display, atom_name, False);
                break;
            }
        }
        XFree(attributes);
    }

    return xv_atom;
}