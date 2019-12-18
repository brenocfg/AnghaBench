#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct kms {scalar_t__ crtc_id; TYPE_3__* encoder; TYPE_1__* connector; int /*<<< orphan*/  fd; } ;
struct TYPE_8__ {unsigned int count_encoders; unsigned int count_crtcs; scalar_t__* crtcs; int /*<<< orphan*/ * encoders; } ;
typedef  TYPE_2__ drmModeRes ;
struct TYPE_9__ {scalar_t__ encoder_id; scalar_t__ crtc_id; int possible_crtcs; } ;
typedef  TYPE_3__ drmModeEncoder ;
struct TYPE_7__ {scalar_t__ encoder_id; scalar_t__ connector_id; unsigned int count_encoders; int /*<<< orphan*/ * encoders; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct kms*,char*,scalar_t__) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct kms*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MP_WARN (struct kms*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drmModeFreeEncoder (TYPE_3__*) ; 
 TYPE_3__* drmModeGetEncoder (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool setup_crtc(struct kms *kms, const drmModeRes *res)
{
    // First try to find currently connected encoder and its current CRTC
    for (unsigned int i = 0; i < res->count_encoders; i++) {
        drmModeEncoder *encoder = drmModeGetEncoder(kms->fd, res->encoders[i]);
        if (!encoder) {
            MP_WARN(kms, "Cannot retrieve encoder %u:%u: %s\n",
                    i, res->encoders[i], mp_strerror(errno));
            continue;
        }

        if (encoder->encoder_id == kms->connector->encoder_id && encoder->crtc_id != 0) {
            MP_VERBOSE(kms, "Connector %u currently connected to encoder %u\n",
                       kms->connector->connector_id, kms->connector->encoder_id);
            kms->encoder = encoder;
            kms->crtc_id = encoder->crtc_id;
            goto success;
        }

        drmModeFreeEncoder(encoder);
    }

    // Otherwise pick first legal encoder and CRTC combo for the connector
    for (unsigned int i = 0; i < kms->connector->count_encoders; ++i) {
        drmModeEncoder *encoder
            = drmModeGetEncoder(kms->fd, kms->connector->encoders[i]);
        if (!encoder) {
            MP_WARN(kms, "Cannot retrieve encoder %u:%u: %s\n",
                    i, kms->connector->encoders[i], mp_strerror(errno));
            continue;
        }

        // iterate all global CRTCs
        for (unsigned int j = 0; j < res->count_crtcs; ++j) {
            // check whether this CRTC works with the encoder
            if (!(encoder->possible_crtcs & (1 << j)))
                continue;

            kms->encoder = encoder;
            kms->crtc_id = res->crtcs[j];
            goto success;
        }

        drmModeFreeEncoder(encoder);
    }

    MP_ERR(kms, "Connector %u has no suitable CRTC\n",
           kms->connector->connector_id);
    return false;

  success:
    MP_VERBOSE(kms, "Selected Encoder %u with CRTC %u\n",
               kms->encoder->encoder_id, kms->crtc_id);
    return true;
}