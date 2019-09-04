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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct snd_kcontrol {size_t private_value; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HPI_ERROR_INVALID_OBJ_INDEX ; 
 scalar_t__ hpi_tuner_query_band (size_t,size_t,scalar_t__*) ; 

__attribute__((used)) static int asihpi_tuner_band_query(struct snd_kcontrol *kcontrol,
					u16 *band_list, u32 len) {
	u32 h_control = kcontrol->private_value;
	u16 err = 0;
	u32 i;

	for (i = 0; i < len; i++) {
		err = hpi_tuner_query_band(
				h_control, i, &band_list[i]);
		if (err != 0)
			break;
	}

	if (err && (err != HPI_ERROR_INVALID_OBJ_INDEX))
		return -EIO;

	return i;
}