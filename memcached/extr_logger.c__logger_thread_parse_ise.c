#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct logentry_item_store {int cmd; size_t status; int /*<<< orphan*/  sfd; int /*<<< orphan*/  clsid; int /*<<< orphan*/  ttl; int /*<<< orphan*/  nkey; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {TYPE_1__ tv; scalar_t__ gid; scalar_t__ data; } ;
typedef  TYPE_2__ logentry ;

/* Variables and functions */
 int KEY_MAX_URI_ENCODED_LENGTH ; 
 int /*<<< orphan*/  LOGGER_PARSE_SCRATCH ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int,int,unsigned long long,char*,char const* const,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uriencode (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _logger_thread_parse_ise(logentry *e, char *scratch) {
    int total;
    const char *cmd = "na";
    char keybuf[KEY_MAX_URI_ENCODED_LENGTH];
    struct logentry_item_store *le = (struct logentry_item_store *) e->data;
    const char * const status_map[] = {
        "not_stored", "stored", "exists", "not_found", "too_large", "no_memory" };
    const char * const cmd_map[] = {
        "null", "add", "set", "replace", "append", "prepend", "cas" };

    if (le->cmd <= 6)
        cmd = cmd_map[le->cmd];

    uriencode(le->key, keybuf, le->nkey, KEY_MAX_URI_ENCODED_LENGTH);
    total = snprintf(scratch, LOGGER_PARSE_SCRATCH,
            "ts=%d.%d gid=%llu type=item_store key=%s status=%s cmd=%s ttl=%u clsid=%u cfd=%d\n",
            (int)e->tv.tv_sec, (int)e->tv.tv_usec, (unsigned long long) e->gid,
            keybuf, status_map[le->status], cmd, le->ttl, le->clsid, le->sfd);
    return total;
}