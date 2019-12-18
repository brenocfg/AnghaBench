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
struct slabinfo {scalar_t__ hash; struct slabinfo* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct slabinfo* callocz (int,int) ; 
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  slabdebug (char*,...) ; 
 struct slabinfo* slabinfo_last_used ; 
 struct slabinfo* slabinfo_next ; 
 struct slabinfo* slabinfo_root ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupz (char const*) ; 

__attribute__((used)) static struct slabinfo *get_slabstruct(const char *name) {
    struct slabinfo *s;

    slabdebug("--> Requested slabstruct %s", name);

    uint32_t hash = simple_hash(name);

    // Search it, from the next to the end
    for (s = slabinfo_next; s; s = s->next) {
        if ((hash = s->hash) && !strcmp(name, s->name)) {
            slabdebug("<-- Found existing slabstruct after %s", slabinfo_last_used->name);
            // Prepare the next run
            slabinfo_next = s->next;
            slabinfo_last_used = s;
            return s;
        }
    }

    // Search it from the begining to the last position we used
    for (s = slabinfo_root; s != slabinfo_last_used; s = s->next) {
        if (hash == s->hash && !strcmp(name, s->name)) {
            slabdebug("<-- Found existing slabstruct after root %s", slabinfo_root->name);
            slabinfo_next = s->next;
            slabinfo_last_used = s;
            return s;
        }
    }

    // Create a new one
    s = callocz(1, sizeof(struct slabinfo));
    s->name = strdupz(name);
    s->hash = hash;

    // Add it to the current postion
    if (slabinfo_root) {
        slabdebug("<-- Creating new slabstruct after %s", slabinfo_last_used->name);
        s->next = slabinfo_last_used->next;
        slabinfo_last_used->next = s;
        slabinfo_last_used = s;
    }
    else {
        slabdebug("<-- Creating new slabstruct as root");
        slabinfo_root = slabinfo_last_used = s;
    }

    return s;
}