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
typedef  int /*<<< orphan*/  uint8_t ;
struct logentry_item_get {int was_found; int nkey; int sfd; int /*<<< orphan*/  key; int /*<<< orphan*/  clsid; } ;
struct TYPE_3__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ logentry ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int const) ; 

__attribute__((used)) static void _logger_log_item_get(logentry *e, const int was_found, const char *key,
        const int nkey, const uint8_t clsid, const int sfd) {
    struct logentry_item_get *le = (struct logentry_item_get *) e->data;
    le->was_found = was_found;
    le->nkey = nkey;
    le->clsid = clsid;
    memcpy(le->key, key, nkey);
    le->sfd = sfd;
    e->size = sizeof(struct logentry_item_get) + nkey;
}