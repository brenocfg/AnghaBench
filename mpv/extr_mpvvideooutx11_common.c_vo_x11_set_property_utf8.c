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
struct vo_x11_state {int /*<<< orphan*/  window; int /*<<< orphan*/  display; } ;
struct vo {struct vo_x11_state* x11; } ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  UTF8_STRING ; 
 int /*<<< orphan*/  XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void vo_x11_set_property_utf8(struct vo *vo, Atom name, const char *t)
{
    struct vo_x11_state *x11 = vo->x11;

    XChangeProperty(x11->display, x11->window, name, XA(x11, UTF8_STRING), 8,
                    PropModeReplace, t, strlen(t));
}