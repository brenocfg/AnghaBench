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
struct kms {TYPE_1__* connector; int /*<<< orphan*/  log; } ;
struct drm_mode_spec {int type; int /*<<< orphan*/  refresh; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  idx; } ;
struct TYPE_2__ {scalar_t__ count_modes; } ;

/* Variables and functions */
#define  DRM_MODE_SPEC_BY_IDX 131 
#define  DRM_MODE_SPEC_BY_NUMBERS 130 
#define  DRM_MODE_SPEC_HIGHEST 129 
#define  DRM_MODE_SPEC_PREFERRED 128 
 int /*<<< orphan*/  MP_ERR (struct kms*,char*) ; 
 int /*<<< orphan*/  MP_INFO (struct kms*,char*) ; 
 int /*<<< orphan*/  kms_show_available_modes (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  parse_mode_spec (char const*,struct drm_mode_spec*) ; 
 int /*<<< orphan*/  setup_mode_by_idx (struct kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_mode_by_numbers (struct kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  setup_mode_highest (struct kms*) ; 
 int /*<<< orphan*/  setup_mode_preferred (struct kms*) ; 

__attribute__((used)) static bool setup_mode(struct kms *kms, const char *mode_spec)
{
    if (kms->connector->count_modes <= 0) {
        MP_ERR(kms, "No available modes\n");
        return false;
    }

    struct drm_mode_spec parsed;
    if (!parse_mode_spec(mode_spec, &parsed)) {
        MP_ERR(kms, "Parse error\n");
        goto err;
    }

    switch (parsed.type) {
    case DRM_MODE_SPEC_BY_IDX:
        if (!setup_mode_by_idx(kms, parsed.idx))
            goto err;
        break;
    case DRM_MODE_SPEC_BY_NUMBERS:
        if (!setup_mode_by_numbers(kms, parsed.width, parsed.height, parsed.refresh,
                                   mode_spec))
            goto err;
        break;
    case DRM_MODE_SPEC_PREFERRED:
        if (!setup_mode_preferred(kms))
            goto err;
        break;
    case DRM_MODE_SPEC_HIGHEST:
        if (!setup_mode_highest(kms))
            goto err;
        break;
    default:
        MP_ERR(kms, "setup_mode: Internal error\n");
        goto err;
    }

    return true;

err:
    MP_INFO(kms, "Available modes:\n");
    kms_show_available_modes(kms->log, kms->connector);
    return false;
}