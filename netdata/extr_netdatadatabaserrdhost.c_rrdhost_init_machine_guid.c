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
struct TYPE_3__ {char* machine_guid; int /*<<< orphan*/  hash_machine_guid; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 size_t GUID_LEN ; 
 int /*<<< orphan*/  simple_hash (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static inline void rrdhost_init_machine_guid(RRDHOST *host, const char *machine_guid) {
    strncpy(host->machine_guid, machine_guid, GUID_LEN);
    host->machine_guid[GUID_LEN] = '\0';
    host->hash_machine_guid = simple_hash(host->machine_guid);
}