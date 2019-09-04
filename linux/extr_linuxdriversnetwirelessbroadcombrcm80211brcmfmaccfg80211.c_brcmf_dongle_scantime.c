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
struct brcmf_if {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_SCAN_CHANNEL_TIME ; 
 int /*<<< orphan*/  BRCMF_C_SET_SCAN_PASSIVE_TIME ; 
 int /*<<< orphan*/  BRCMF_C_SET_SCAN_UNASSOC_TIME ; 
 int /*<<< orphan*/  BRCMF_SCAN_CHANNEL_TIME ; 
 int /*<<< orphan*/  BRCMF_SCAN_PASSIVE_TIME ; 
 int /*<<< orphan*/  BRCMF_SCAN_UNASSOC_TIME ; 
 int /*<<< orphan*/  brcmf_err (char*,scalar_t__) ; 
 scalar_t__ brcmf_fil_cmd_int_set (struct brcmf_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32
brcmf_dongle_scantime(struct brcmf_if *ifp)
{
	s32 err = 0;

	err = brcmf_fil_cmd_int_set(ifp, BRCMF_C_SET_SCAN_CHANNEL_TIME,
				    BRCMF_SCAN_CHANNEL_TIME);
	if (err) {
		brcmf_err("Scan assoc time error (%d)\n", err);
		goto dongle_scantime_out;
	}
	err = brcmf_fil_cmd_int_set(ifp, BRCMF_C_SET_SCAN_UNASSOC_TIME,
				    BRCMF_SCAN_UNASSOC_TIME);
	if (err) {
		brcmf_err("Scan unassoc time error (%d)\n", err);
		goto dongle_scantime_out;
	}

	err = brcmf_fil_cmd_int_set(ifp, BRCMF_C_SET_SCAN_PASSIVE_TIME,
				    BRCMF_SCAN_PASSIVE_TIME);
	if (err) {
		brcmf_err("Scan passive time error (%d)\n", err);
		goto dongle_scantime_out;
	}

dongle_scantime_out:
	return err;
}