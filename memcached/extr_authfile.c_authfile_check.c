#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t ulen; size_t plen; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; } ;
typedef  TYPE_1__ auth_t ;

/* Variables and functions */
 int entry_cnt ; 
 TYPE_1__* main_auth_entries ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 

int authfile_check(const char *user, const char *pass) {
    size_t ulen = strlen(user);
    size_t plen = strlen(pass);

    for (int x = 0; x < entry_cnt; x++) {
        auth_t *e = &main_auth_entries[x];
        if (ulen == e->ulen && plen == e->plen &&
            memcmp(user, e->user, e->ulen) == 0 &&
            memcmp(pass, e->pass, e->plen) == 0) {
            return 1;
        }
    }

    return 0;
}