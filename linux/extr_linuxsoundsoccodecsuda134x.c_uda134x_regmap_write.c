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
typedef  int u8 ;
struct uda134x_platform_data {int /*<<< orphan*/  l3; } ;

/* Variables and functions */
 int EIO ; 
#define  UDA134X_DATA000 134 
#define  UDA134X_DATA001 133 
#define  UDA134X_DATA010 132 
#define  UDA134X_DATA011 131 
 int UDA134X_DATA0_ADDR ; 
#define  UDA134X_DATA1 130 
 int UDA134X_DATA1_ADDR ; 
 unsigned int UDA134X_EXTADDR_PREFIX ; 
 unsigned int UDA134X_EXTDATA_PREFIX ; 
#define  UDA134X_STATUS0 129 
#define  UDA134X_STATUS1 128 
 int UDA134X_STATUS_ADDR ; 
 int l3_write (int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static int uda134x_regmap_write(void *context, unsigned int reg,
	unsigned int value)
{
	struct uda134x_platform_data *pd = context;
	int ret;
	u8 addr;
	u8 data = value;

	switch (reg) {
	case UDA134X_STATUS0:
	case UDA134X_STATUS1:
		addr = UDA134X_STATUS_ADDR;
		data |= (reg - UDA134X_STATUS0) << 7;
		break;
	case UDA134X_DATA000:
	case UDA134X_DATA001:
	case UDA134X_DATA010:
	case UDA134X_DATA011:
		addr = UDA134X_DATA0_ADDR;
		data |= (reg - UDA134X_DATA000) << 6;
		break;
	case UDA134X_DATA1:
		addr = UDA134X_DATA1_ADDR;
		break;
	default:
		/* It's an extended address register */
		addr =  (reg | UDA134X_EXTADDR_PREFIX);

		ret = l3_write(&pd->l3,
			       UDA134X_DATA0_ADDR, &addr, 1);
		if (ret != 1)
			return -EIO;

		addr = UDA134X_DATA0_ADDR;
		data = (value | UDA134X_EXTDATA_PREFIX);
		break;
	}

	ret = l3_write(&pd->l3,
		       addr, &data, 1);
	if (ret != 1)
		return -EIO;

	return 0;
}