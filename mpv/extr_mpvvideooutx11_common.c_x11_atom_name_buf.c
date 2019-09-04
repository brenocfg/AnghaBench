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
struct vo_x11_state {int /*<<< orphan*/  display; } ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  XFree (char*) ; 
 char* XGetAtomName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static char *x11_atom_name_buf(struct vo_x11_state *x11, Atom atom,
                               char *buf, size_t buf_size)
{
    buf[0] = '\0';

    char *new_name = XGetAtomName(x11->display, atom);
    if (new_name) {
        snprintf(buf, buf_size, "%s", new_name);
        XFree(new_name);
    }

    return buf;
}