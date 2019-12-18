#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  report_id; int /*<<< orphan*/  mods; } ;
struct TYPE_8__ {int /*<<< orphan*/ * raw; int /*<<< orphan*/  report_id; TYPE_1__ nkro; int /*<<< orphan*/  mods; } ;
typedef  TYPE_2__ report_keyboard_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* send_keyboard ) (TYPE_2__*) ;} ;
struct TYPE_9__ {scalar_t__ nkro; } ;

/* Variables and functions */
 size_t KEYBOARD_REPORT_SIZE ; 
 int /*<<< orphan*/  REPORT_ID_KEYBOARD ; 
 int /*<<< orphan*/  REPORT_ID_NKRO ; 
 scalar_t__ debug_keyboard ; 
 int /*<<< orphan*/  dprint (char*) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* driver ; 
 scalar_t__ keyboard_protocol ; 
 TYPE_4__ keymap_config ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void host_keyboard_send(report_keyboard_t *report) {
    if (!driver) return;
#if defined(NKRO_ENABLE) && defined(NKRO_SHARED_EP)
    if (keyboard_protocol && keymap_config.nkro) {
        /* The callers of this function assume that report->mods is where mods go in.
         * But report->nkro.mods can be at a different offset if core keyboard does not have a report ID.
         */
        report->nkro.mods      = report->mods;
        report->nkro.report_id = REPORT_ID_NKRO;
    } else
#endif
    {
#ifdef KEYBOARD_SHARED_EP
        report->report_id = REPORT_ID_KEYBOARD;
#endif
    }
    (*driver->send_keyboard)(report);

    if (debug_keyboard) {
        dprint("keyboard_report: ");
        for (uint8_t i = 0; i < KEYBOARD_REPORT_SIZE; i++) {
            dprintf("%02X ", report->raw[i]);
        }
        dprint("\n");
    }
}