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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  avl ;
struct TYPE_3__ {int /*<<< orphan*/  machine_guid; scalar_t__ hash_machine_guid; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_RRDHOST ; 
 int /*<<< orphan*/  GUID_LEN ; 
 scalar_t__ avl_search_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  rrdhost_root_index ; 
 scalar_t__ simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpyz (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

RRDHOST *rrdhost_find_by_guid(const char *guid, uint32_t hash) {
    debug(D_RRDHOST, "Searching in index for host with guid '%s'", guid);

    RRDHOST tmp;
    strncpyz(tmp.machine_guid, guid, GUID_LEN);
    tmp.hash_machine_guid = (hash)?hash:simple_hash(tmp.machine_guid);

    return (RRDHOST *)avl_search_lock(&(rrdhost_root_index), (avl *) &tmp);
}