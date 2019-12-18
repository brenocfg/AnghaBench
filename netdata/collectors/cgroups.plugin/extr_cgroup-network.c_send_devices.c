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
struct found_device {char* host_device; char* guest_device; struct found_device* next; } ;

/* Variables and functions */
 struct found_device* detected_devices ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

int send_devices(void) {
    int found = 0;

    struct found_device *f;
    for(f = detected_devices; f ; f = f->next) {
        found++;
        printf("%s %s\n", f->host_device, (f->guest_device)?f->guest_device:f->host_device);
    }

    return found;
}