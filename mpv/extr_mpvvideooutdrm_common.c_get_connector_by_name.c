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
struct kms {int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {int count_connectors; int /*<<< orphan*/ * connectors; } ;
typedef  TYPE_1__ drmModeRes ;
typedef  int /*<<< orphan*/  drmModeConnector ;

/* Variables and functions */
 int MAX_CONNECTOR_NAME_LEN ; 
 int /*<<< orphan*/  drmModeFreeConnector (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * drmModeGetConnector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_connector_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static drmModeConnector *get_connector_by_name(const struct kms *kms,
                                               const drmModeRes *res,
                                               const char *connector_name)
{
    for (int i = 0; i < res->count_connectors; i++) {
        drmModeConnector *connector
            = drmModeGetConnector(kms->fd, res->connectors[i]);
        if (!connector)
            continue;
        char other_connector_name[MAX_CONNECTOR_NAME_LEN];
        get_connector_name(connector, other_connector_name);
        if (!strcmp(connector_name, other_connector_name))
            return connector;
        drmModeFreeConnector(connector);
    }
    return NULL;
}