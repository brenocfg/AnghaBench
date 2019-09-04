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
struct BannerOutput {scalar_t__ length; scalar_t__ max_length; scalar_t__ banner; } ;

/* Variables and functions */
 size_t AUTO_LEN ; 
 struct BannerOutput* banout_expand (struct BannerOutput*,struct BannerOutput*) ; 
 struct BannerOutput* banout_find_proto (struct BannerOutput*,unsigned int) ; 
 struct BannerOutput* banout_new_proto (struct BannerOutput*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 size_t strlen (char const*) ; 

void
banout_append(struct BannerOutput *banout, unsigned proto, 
              const void *px, size_t length)
{
    struct BannerOutput *p;

    if (length == AUTO_LEN)
        length = strlen((const char*)px);
    
    /*
     * Get the matching record for the protocol (e.g. HTML, SSL, etc.).
     * If it doesn't already exist, add the protocol object to the linked
     * list.
     */
    p = banout_find_proto(banout, proto);
    if (p == NULL) {
        p = banout_new_proto(banout, proto);
    }


    /*
     * If the current object isn't big enough, expand it
     */
    while (p->length + length >= p->max_length) {
        p = banout_expand(banout, p);
    }

    
    
    /*
     * Now that we are assured there is enough space, do the copy
     */
    memcpy(p->banner + p->length, px, length);
    p->length = (unsigned)(p->length + length);

}