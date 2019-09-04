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
typedef  int /*<<< orphan*/  uint32_t ;
struct vo {TYPE_1__* x11; } ;
struct TYPE_6__ {int flags; char const* name; int min_value; int max_value; } ;
typedef  TYPE_2__ XvAttribute ;
struct TYPE_5__ {int /*<<< orphan*/  display; } ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 scalar_t__ None ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XFree (TYPE_2__*) ; 
 scalar_t__ XInternAtom (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int XvGettable ; 
 TYPE_2__* XvQueryPortAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int XvSettable ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int xv_find_atom(struct vo *vo, uint32_t xv_port, const char *name,
                        bool get, int *min, int *max)
{
    Atom atom = None;
    int howmany = 0;
    XvAttribute *attributes = XvQueryPortAttributes(vo->x11->display, xv_port,
                                                    &howmany);
    for (int i = 0; i < howmany && attributes; i++) {
        int flag = get ? XvGettable : XvSettable;
        if (attributes[i].flags & flag) {
            atom = XInternAtom(vo->x11->display, attributes[i].name, True);
            *min = attributes[i].min_value;
            *max = attributes[i].max_value;
/* since we have SET_DEFAULTS first in our list, we can check if it's available
   then trigger it if it's ok so that the other values are at default upon query */
            if (atom != None) {
                if (!strcmp(attributes[i].name, "XV_BRIGHTNESS") &&
                    (!strcmp(name, "brightness")))
                    break;
                else if (!strcmp(attributes[i].name, "XV_CONTRAST") &&
                         (!strcmp(name, "contrast")))
                    break;
                else if (!strcmp(attributes[i].name, "XV_SATURATION") &&
                         (!strcmp(name, "saturation")))
                    break;
                else if (!strcmp(attributes[i].name, "XV_HUE") &&
                         (!strcmp(name, "hue")))
                    break;
                if (!strcmp(attributes[i].name, "XV_RED_INTENSITY") &&
                    (!strcmp(name, "red_intensity")))
                    break;
                else if (!strcmp(attributes[i].name, "XV_GREEN_INTENSITY")
                         && (!strcmp(name, "green_intensity")))
                    break;
                else if (!strcmp(attributes[i].name, "XV_BLUE_INTENSITY")
                         && (!strcmp(name, "blue_intensity")))
                    break;
                else if ((!strcmp(attributes[i].name, "XV_ITURBT_709") //NVIDIA
                          || !strcmp(attributes[i].name, "XV_COLORSPACE")) //ATI
                         && (!strcmp(name, "bt_709")))
                    break;
                atom = None;
                continue;
            }
        }
    }
    XFree(attributes);
    return atom;
}