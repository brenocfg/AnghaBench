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
 int /*<<< orphan*/  kms_show_available_connectors_and_modes ; 
 int /*<<< orphan*/  kms_show_foreach_card (struct mp_log*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kms_show_available_cards_connectors_and_modes(struct mp_log *log)
{
    kms_show_foreach_card(log, kms_show_available_connectors_and_modes);
}