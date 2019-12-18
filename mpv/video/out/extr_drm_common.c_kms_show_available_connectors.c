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
struct mp_log {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kms_show_connector_name_and_state_callback ; 
 int /*<<< orphan*/  kms_show_foreach_connector (struct mp_log*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 

__attribute__((used)) static void kms_show_available_connectors(struct mp_log *log, int card_no)
{
    mp_info(log, "Available connectors for card %d:\n", card_no);
    kms_show_foreach_connector(
        log, card_no, kms_show_connector_name_and_state_callback);
    mp_info(log, "\n");
}