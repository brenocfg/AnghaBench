#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct asus_wmi {int spec; int sfun; int /*<<< orphan*/  platform_device; TYPE_2__* driver; int /*<<< orphan*/  dsts_id; } ;
struct TYPE_4__ {TYPE_1__* quirks; } ;
struct TYPE_3__ {scalar_t__ wapf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_CWAP ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_DSTS ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_DSTS2 ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_INIT ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_SFUN ; 
 int /*<<< orphan*/  ASUS_WMI_METHODID_SPEC ; 
 int /*<<< orphan*/  asus_wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  asus_wmi_set_devstate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int asus_wmi_sysfs_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 

__attribute__((used)) static int asus_wmi_platform_init(struct asus_wmi *asus)
{
	int rv;

	/* INIT enable hotkeys on some models */
	if (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_INIT, 0, 0, &rv))
		pr_info("Initialization: %#x\n", rv);

	/* We don't know yet what to do with this version... */
	if (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_SPEC, 0, 0x9, &rv)) {
		pr_info("BIOS WMI version: %d.%d\n", rv >> 16, rv & 0xFF);
		asus->spec = rv;
	}

	/*
	 * The SFUN method probably allows the original driver to get the list
	 * of features supported by a given model. For now, 0x0100 or 0x0800
	 * bit signifies that the laptop is equipped with a Wi-Fi MiniPCI card.
	 * The significance of others is yet to be found.
	 */
	if (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_SFUN, 0, 0, &rv)) {
		pr_info("SFUN value: %#x\n", rv);
		asus->sfun = rv;
	}

	/*
	 * Eee PC and Notebooks seems to have different method_id for DSTS,
	 * but it may also be related to the BIOS's SPEC.
	 * Note, on most Eeepc, there is no way to check if a method exist
	 * or note, while on notebooks, they returns 0xFFFFFFFE on failure,
	 * but once again, SPEC may probably be used for that kind of things.
	 */
	if (!asus_wmi_evaluate_method(ASUS_WMI_METHODID_DSTS, 0, 0, NULL))
		asus->dsts_id = ASUS_WMI_METHODID_DSTS;
	else
		asus->dsts_id = ASUS_WMI_METHODID_DSTS2;

	/* CWAP allow to define the behavior of the Fn+F2 key,
	 * this method doesn't seems to be present on Eee PCs */
	if (asus->driver->quirks->wapf >= 0)
		asus_wmi_set_devstate(ASUS_WMI_DEVID_CWAP,
				      asus->driver->quirks->wapf, NULL);

	return asus_wmi_sysfs_init(asus->platform_device);
}