#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct kms {int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {int count_connectors; int /*<<< orphan*/ * connectors; } ;
typedef  TYPE_1__ drmModeRes ;
struct TYPE_8__ {scalar_t__ connection; scalar_t__ count_modes; } ;
typedef  TYPE_2__ drmModeConnector ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTED ; 
 int /*<<< orphan*/  drmModeFreeConnector (TYPE_2__*) ; 
 TYPE_2__* drmModeGetConnector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static drmModeConnector *get_first_connected_connector(const struct kms *kms,
                                                       const drmModeRes *res)
{
    for (int i = 0; i < res->count_connectors; i++) {
        drmModeConnector *connector
            = drmModeGetConnector(kms->fd, res->connectors[i]);
        if (!connector)
            continue;
        if (connector->connection == DRM_MODE_CONNECTED
        && connector->count_modes > 0) {
            return connector;
        }
        drmModeFreeConnector(connector);
    }
    return NULL;
}