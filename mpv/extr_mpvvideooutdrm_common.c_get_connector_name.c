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
struct TYPE_3__ {size_t connector_type; int connector_type_id; } ;
typedef  TYPE_1__ drmModeConnector ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CONNECTOR_NAME_LEN ; 
 char** connector_names ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void get_connector_name(const drmModeConnector *connector,
                               char ret[MAX_CONNECTOR_NAME_LEN])
{
    snprintf(ret, MAX_CONNECTOR_NAME_LEN, "%s-%d",
             connector_names[connector->connector_type],
             connector->connector_type_id);
}