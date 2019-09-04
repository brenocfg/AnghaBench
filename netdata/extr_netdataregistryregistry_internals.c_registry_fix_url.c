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
struct TYPE_2__ {size_t max_url_length; } ;

/* Variables and functions */
 TYPE_1__ registry ; 
 char* registry_fix_machine_name (char*,size_t*) ; 

__attribute__((used)) static inline char *registry_fix_url(char *url, size_t *len) {
    size_t l = 0;
    char *s = registry_fix_machine_name(url, &l);

    // protection from too big URLs
    if(l > registry.max_url_length) {
        l = registry.max_url_length;
        s[l] = '\0';
    }

    if(len) *len = l;
    return s;
}