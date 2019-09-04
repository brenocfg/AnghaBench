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
struct TYPE_2__ {char* bdf_ext; } ;
struct ath10k {TYPE_1__ id; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  ath10k_core_check_bdfext ; 
 int /*<<< orphan*/  dmi_walk (int /*<<< orphan*/ ,struct ath10k*) ; 

__attribute__((used)) static int ath10k_core_check_smbios(struct ath10k *ar)
{
	ar->id.bdf_ext[0] = '\0';
	dmi_walk(ath10k_core_check_bdfext, ar);

	if (ar->id.bdf_ext[0] == '\0')
		return -ENODATA;

	return 0;
}