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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ hash; int /*<<< orphan*/  value; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  RRDR_GROUPING ;

/* Variables and functions */
 TYPE_1__* api_v1_data_groups ; 
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

RRDR_GROUPING web_client_api_request_v1_data_group(const char *name, RRDR_GROUPING def) {
    int i;

    uint32_t hash = simple_hash(name);
    for(i = 0; api_v1_data_groups[i].name ; i++)
        if(unlikely(hash == api_v1_data_groups[i].hash && !strcmp(name, api_v1_data_groups[i].name)))
            return api_v1_data_groups[i].value;

    return def;
}