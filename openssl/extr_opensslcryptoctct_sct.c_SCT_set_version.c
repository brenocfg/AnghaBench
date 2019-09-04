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
typedef  scalar_t__ sct_version_t ;
struct TYPE_3__ {int /*<<< orphan*/  validation_status; scalar_t__ version; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_SCT_SET_VERSION ; 
 int /*<<< orphan*/  CT_R_UNSUPPORTED_VERSION ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCT_VALIDATION_STATUS_NOT_SET ; 
 scalar_t__ SCT_VERSION_V1 ; 

int SCT_set_version(SCT *sct, sct_version_t version)
{
    if (version != SCT_VERSION_V1) {
        CTerr(CT_F_SCT_SET_VERSION, CT_R_UNSUPPORTED_VERSION);
        return 0;
    }
    sct->version = version;
    sct->validation_status = SCT_VALIDATION_STATUS_NOT_SET;
    return 1;
}