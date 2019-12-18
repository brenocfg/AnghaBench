#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bluray_priv_s {int /*<<< orphan*/  bd; } ;
struct TYPE_6__ {struct bluray_priv_s* priv; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  bdplus_handled; int /*<<< orphan*/  libbdplus_detected; scalar_t__ bdplus_detected; int /*<<< orphan*/  aacs_error_code; int /*<<< orphan*/  aacs_handled; int /*<<< orphan*/  libaacs_detected; scalar_t__ aacs_detected; int /*<<< orphan*/  bluray_detected; } ;
typedef  TYPE_2__ BLURAY_DISC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  aacs_strerr (int /*<<< orphan*/ ) ; 
 TYPE_2__* bd_get_disc_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_disc_info(stream_t *s)
{
    struct bluray_priv_s *b = s->priv;
    const BLURAY_DISC_INFO *info = bd_get_disc_info(b->bd);

    // check Blu-ray
    if (!info->bluray_detected) {
        MP_ERR(s, "Given stream is not a Blu-ray.\n");
        return false;
    }

    // check AACS
    if (info->aacs_detected) {
        if (!info->libaacs_detected) {
            MP_ERR(s, "AACS encryption detected but cannot find libaacs.\n");
            return false;
        }
        if (!info->aacs_handled) {
            MP_ERR(s, "AACS error: %s\n", aacs_strerr(info->aacs_error_code));
            return false;
        }
    }

    // check BD+
    if (info->bdplus_detected) {
        if (!info->libbdplus_detected) {
            MP_ERR(s, "BD+ encryption detected but cannot find libbdplus.\n");
            return false;
        }
        if (!info->bdplus_handled) {
            MP_ERR(s, "Cannot decrypt BD+ encryption.\n");
            return false;
        }
    }

    return true;
}