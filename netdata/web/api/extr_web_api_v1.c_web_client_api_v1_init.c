#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct TYPE_6__ {scalar_t__ name; void* hash; } ;
struct TYPE_5__ {scalar_t__ name; void* hash; } ;
struct TYPE_4__ {scalar_t__ name; void* hash; } ;

/* Variables and functions */
 TYPE_3__* api_v1_data_formats ; 
 TYPE_2__* api_v1_data_google_formats ; 
 TYPE_1__* api_v1_data_options ; 
 void* simple_hash (scalar_t__) ; 
 int /*<<< orphan*/  uuid_generate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_unparse_lower (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  web_client_api_v1_init_grouping () ; 

void web_client_api_v1_init(void) {
    int i;

    for(i = 0; api_v1_data_options[i].name ; i++)
        api_v1_data_options[i].hash = simple_hash(api_v1_data_options[i].name);

    for(i = 0; api_v1_data_formats[i].name ; i++)
        api_v1_data_formats[i].hash = simple_hash(api_v1_data_formats[i].name);

    for(i = 0; api_v1_data_google_formats[i].name ; i++)
        api_v1_data_google_formats[i].hash = simple_hash(api_v1_data_google_formats[i].name);

    web_client_api_v1_init_grouping();

	uuid_t uuid;

	// generate
	uuid_generate(uuid);

	// unparse (to string)
	char uuid_str[37];
	uuid_unparse_lower(uuid, uuid_str);
}