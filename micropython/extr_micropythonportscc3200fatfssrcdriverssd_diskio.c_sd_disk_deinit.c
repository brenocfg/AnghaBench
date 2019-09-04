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
struct TYPE_2__ {scalar_t__ usRCA; int /*<<< orphan*/  bStatus; scalar_t__ ulBlockSize; scalar_t__ ulNofBlock; int /*<<< orphan*/  ulCapClass; int /*<<< orphan*/  ulVersion; int /*<<< orphan*/  ucCardType; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_CAP_CLASS_SDSC ; 
 int /*<<< orphan*/  CARD_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  CARD_VERSION_1 ; 
 int /*<<< orphan*/  STA_NOINIT ; 
 TYPE_1__ sd_disk_info ; 

void sd_disk_deinit (void) {
    sd_disk_info.ucCardType = CARD_TYPE_UNKNOWN;
    sd_disk_info.ulVersion = CARD_VERSION_1;
    sd_disk_info.ulCapClass = CARD_CAP_CLASS_SDSC;
    sd_disk_info.ulNofBlock = 0;
    sd_disk_info.ulBlockSize = 0;
    sd_disk_info.bStatus = STA_NOINIT;
    sd_disk_info.usRCA = 0;
}