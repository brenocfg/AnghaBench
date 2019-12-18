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
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hdspm {int io_type; scalar_t__ tco; } ;

/* Variables and functions */
#define  AES32 132 
#define  AIO 131 
 int /*<<< orphan*/  HDSPM_TCO1_LTC_Input_valid ; 
 int /*<<< orphan*/  HDSPM_TCO1_TCO_lock ; 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 int hdspm_aes_sync_check (struct hdspm*,int) ; 
 int hdspm_madi_sync_check (struct hdspm*) ; 
 int hdspm_s1_sync_check (struct hdspm*,int) ; 
 int hdspm_sync_in_sync_check (struct hdspm*) ; 
 int hdspm_tco_input_check (struct hdspm*,int /*<<< orphan*/ ) ; 
 int hdspm_tco_sync_check (struct hdspm*) ; 
 int hdspm_wc_sync_check (struct hdspm*) ; 
 struct hdspm* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_hdspm_get_sync_check(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	int val = -1;

	switch (hdspm->io_type) {
	case RayDAT:
		switch (kcontrol->private_value) {
		case 0: /* WC */
			val = hdspm_wc_sync_check(hdspm); break;
		case 7: /* TCO */
			val = hdspm_tco_sync_check(hdspm); break;
		case 8: /* SYNC IN */
			val = hdspm_sync_in_sync_check(hdspm); break;
		default:
			val = hdspm_s1_sync_check(hdspm,
					kcontrol->private_value-1);
		}
		break;

	case AIO:
		switch (kcontrol->private_value) {
		case 0: /* WC */
			val = hdspm_wc_sync_check(hdspm); break;
		case 4: /* TCO */
			val = hdspm_tco_sync_check(hdspm); break;
		case 5: /* SYNC IN */
			val = hdspm_sync_in_sync_check(hdspm); break;
		default:
			val = hdspm_s1_sync_check(hdspm,
					kcontrol->private_value-1);
		}
		break;

	case MADI:
		switch (kcontrol->private_value) {
		case 0: /* WC */
			val = hdspm_wc_sync_check(hdspm); break;
		case 1: /* MADI */
			val = hdspm_madi_sync_check(hdspm); break;
		case 2: /* TCO */
			val = hdspm_tco_sync_check(hdspm); break;
		case 3: /* SYNC_IN */
			val = hdspm_sync_in_sync_check(hdspm); break;
		}
		break;

	case MADIface:
		val = hdspm_madi_sync_check(hdspm); /* MADI */
		break;

	case AES32:
		switch (kcontrol->private_value) {
		case 0: /* WC */
			val = hdspm_wc_sync_check(hdspm); break;
		case 9: /* TCO */
			val = hdspm_tco_sync_check(hdspm); break;
		case 10 /* SYNC IN */:
			val = hdspm_sync_in_sync_check(hdspm); break;
		default: /* AES1 to AES8 */
			 val = hdspm_aes_sync_check(hdspm,
					 kcontrol->private_value-1);
		}
		break;

	}

	if (hdspm->tco) {
		switch (kcontrol->private_value) {
		case 11:
			/* Check TCO for lock state of its current input */
			val = hdspm_tco_input_check(hdspm, HDSPM_TCO1_TCO_lock);
			break;
		case 12:
			/* Check TCO for valid time code on LTC input. */
			val = hdspm_tco_input_check(hdspm,
				HDSPM_TCO1_LTC_Input_valid);
			break;
		default:
			break;
		}
	}

	if (-1 == val)
		val = 3;

	ucontrol->value.enumerated.item[0] = val;
	return 0;
}