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
typedef  scalar_t__ uint32_t ;
struct found_device {scalar_t__ host_device_hash; char const* host_device; char const* guest_device; struct found_device* next; } ;

/* Variables and functions */
 struct found_device* detected_devices ; 
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  info (char*,char const*,char const*) ; 
 struct found_device* mallocz (int) ; 
 scalar_t__ simple_hash (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char const* strdupz (char const*) ; 

void add_device(const char *host, const char *guest) {
#ifdef NETDATA_INTERNAL_CHECKS
    info("adding device with host '%s', guest '%s'", host, guest);
#endif

    uint32_t hash = simple_hash(host);

    if(guest && (!*guest || strcmp(host, guest) == 0))
        guest = NULL;

    struct found_device *f;
    for(f = detected_devices; f ; f = f->next) {
        if(f->host_device_hash == hash && !strcmp(host, f->host_device)) {

            if(guest && (!f->guest_device || !strcmp(f->host_device, f->guest_device))) {
                if(f->guest_device) freez((void *)f->guest_device);
                f->guest_device = strdupz(guest);
            }

            return;
        }
    }

    f = mallocz(sizeof(struct found_device));
    f->host_device = strdupz(host);
    f->host_device_hash = hash;
    f->guest_device = (guest)?strdupz(guest):NULL;
    f->next = detected_devices;
    detected_devices = f;
}