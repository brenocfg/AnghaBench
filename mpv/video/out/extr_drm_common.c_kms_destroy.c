#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kms {int /*<<< orphan*/  fd; scalar_t__ atomic_context; int /*<<< orphan*/ * encoder; int /*<<< orphan*/ * connector; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drmModeFreeConnector (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drmModeFreeEncoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_atomic_destroy_context (scalar_t__) ; 
 int /*<<< orphan*/  drm_mode_destroy_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct kms*) ; 

void kms_destroy(struct kms *kms)
{
    if (!kms)
        return;
    drm_mode_destroy_blob(kms->fd, &kms->mode);
    if (kms->connector) {
        drmModeFreeConnector(kms->connector);
        kms->connector = NULL;
    }
    if (kms->encoder) {
        drmModeFreeEncoder(kms->encoder);
        kms->encoder = NULL;
    }
    if (kms->atomic_context) {
       drm_atomic_destroy_context(kms->atomic_context);
    }

    close(kms->fd);
    talloc_free(kms);
}