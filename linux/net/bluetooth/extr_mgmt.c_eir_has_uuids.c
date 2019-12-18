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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
#define  EIR_UUID128_ALL 133 
#define  EIR_UUID128_SOME 132 
#define  EIR_UUID16_ALL 131 
#define  EIR_UUID16_SOME 130 
#define  EIR_UUID32_ALL 129 
#define  EIR_UUID32_SOME 128 
 scalar_t__* bluetooth_base_uuid ; 
 int /*<<< orphan*/  has_uuid (scalar_t__*,scalar_t__,scalar_t__**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static bool eir_has_uuids(u8 *eir, u16 eir_len, u16 uuid_count, u8 (*uuids)[16])
{
	u16 parsed = 0;

	while (parsed < eir_len) {
		u8 field_len = eir[0];
		u8 uuid[16];
		int i;

		if (field_len == 0)
			break;

		if (eir_len - parsed < field_len + 1)
			break;

		switch (eir[1]) {
		case EIR_UUID16_ALL:
		case EIR_UUID16_SOME:
			for (i = 0; i + 3 <= field_len; i += 2) {
				memcpy(uuid, bluetooth_base_uuid, 16);
				uuid[13] = eir[i + 3];
				uuid[12] = eir[i + 2];
				if (has_uuid(uuid, uuid_count, uuids))
					return true;
			}
			break;
		case EIR_UUID32_ALL:
		case EIR_UUID32_SOME:
			for (i = 0; i + 5 <= field_len; i += 4) {
				memcpy(uuid, bluetooth_base_uuid, 16);
				uuid[15] = eir[i + 5];
				uuid[14] = eir[i + 4];
				uuid[13] = eir[i + 3];
				uuid[12] = eir[i + 2];
				if (has_uuid(uuid, uuid_count, uuids))
					return true;
			}
			break;
		case EIR_UUID128_ALL:
		case EIR_UUID128_SOME:
			for (i = 0; i + 17 <= field_len; i += 16) {
				memcpy(uuid, eir + i + 2, 16);
				if (has_uuid(uuid, uuid_count, uuids))
					return true;
			}
			break;
		}

		parsed += field_len + 1;
		eir += field_len + 1;
	}

	return false;
}