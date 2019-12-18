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
struct llc_sap {int dummy; } ;

/* Variables and functions */
 int LLC_SAP_DYN_START ; 
 int LLC_SAP_DYN_STOP ; 
 int LLC_SAP_DYN_TRIES ; 
 struct llc_sap* llc_sap_find (int) ; 
 int /*<<< orphan*/  llc_sap_put (struct llc_sap*) ; 
 int llc_ui_sap_last_autoport ; 

__attribute__((used)) static int llc_ui_autoport(void)
{
	struct llc_sap *sap;
	int i, tries = 0;

	while (tries < LLC_SAP_DYN_TRIES) {
		for (i = llc_ui_sap_last_autoport;
		     i < LLC_SAP_DYN_STOP; i += 2) {
			sap = llc_sap_find(i);
			if (!sap) {
				llc_ui_sap_last_autoport = i + 2;
				goto out;
			}
			llc_sap_put(sap);
		}
		llc_ui_sap_last_autoport = LLC_SAP_DYN_START;
		tries++;
	}
	i = 0;
out:
	return i;
}