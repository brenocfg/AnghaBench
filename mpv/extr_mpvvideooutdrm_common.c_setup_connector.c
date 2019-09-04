#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kms {TYPE_1__* connector; int /*<<< orphan*/  card_no; int /*<<< orphan*/  log; } ;
typedef  int /*<<< orphan*/  drmModeRes ;
struct TYPE_5__ {scalar_t__ connection; scalar_t__ count_modes; } ;
typedef  TYPE_1__ drmModeConnector ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTED ; 
 int /*<<< orphan*/  MP_ERR (struct kms*,char*,...) ; 
 int /*<<< orphan*/  drmModeFreeConnector (TYPE_1__*) ; 
 TYPE_1__* get_connector_by_name (struct kms*,int /*<<< orphan*/  const*,char const*) ; 
 TYPE_1__* get_first_connected_connector (struct kms*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kms_show_available_connectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool setup_connector(struct kms *kms, const drmModeRes *res,
                            const char *connector_name)
{
    drmModeConnector *connector;

    if (connector_name
    && strcmp(connector_name, "")
    && strcmp(connector_name, "auto")) {
        connector = get_connector_by_name(kms, res, connector_name);
        if (!connector) {
            MP_ERR(kms, "No connector with name %s found\n", connector_name);
            kms_show_available_connectors(kms->log, kms->card_no);
            return false;
        }
    } else {
        connector = get_first_connected_connector(kms, res);
        if (!connector) {
            MP_ERR(kms, "No connected connectors found\n");
            return false;
        }
    }

    if (connector->connection != DRM_MODE_CONNECTED) {
        drmModeFreeConnector(connector);
        MP_ERR(kms, "Chosen connector is disconnected\n");
        return false;
    }

    if (connector->count_modes == 0) {
        drmModeFreeConnector(connector);
        MP_ERR(kms, "Chosen connector has no valid modes\n");
        return false;
    }

    kms->connector = connector;
    return true;
}