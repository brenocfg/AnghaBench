#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ao_device_list {scalar_t__ num_devices; int /*<<< orphan*/  devices; } ;
struct ao_device_desc {char* desc; char* name; } ;
struct ao {TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct ao_device_list*,int /*<<< orphan*/ ,scalar_t__,struct ao_device_desc) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 void* talloc_asprintf (struct ao_device_list*,char*,char const*,char*) ; 
 void* talloc_strdup (struct ao_device_list*,char const*) ; 

void ao_device_list_add(struct ao_device_list *list, struct ao *ao,
                        struct ao_device_desc *e)
{
    struct ao_device_desc c = *e;
    const char *dname = ao->driver->name;
    char buf[80];
    if (!c.desc || !c.desc[0]) {
        if (c.name && c.name[0]) {
            c.desc = c.name;
        } else if (list->num_devices) {
            // Assume this is the default device.
            snprintf(buf, sizeof(buf), "Default (%s)", dname);
            c.desc = buf;
        } else {
            // First default device (and maybe the only one).
            c.desc = "Default";
        }
    }
    c.name = (c.name && c.name[0]) ? talloc_asprintf(list, "%s/%s", dname, c.name)
                                   : talloc_strdup(list, dname);
    c.desc = talloc_strdup(list, c.desc);
    MP_TARRAY_APPEND(list, list->devices, list->num_devices, c);
}