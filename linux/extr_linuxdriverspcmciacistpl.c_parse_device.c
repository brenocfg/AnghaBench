#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_7__ {int TupleDataLen; scalar_t__ TupleData; } ;
typedef  TYPE_2__ tuple_t ;
struct TYPE_8__ {scalar_t__ ndev; TYPE_1__* dev; } ;
typedef  TYPE_3__ cistpl_device_t ;
struct TYPE_6__ {int type; int wp; int speed; int size; } ;

/* Variables and functions */
 int CISTPL_MAX_DEVICES ; 
 int EINVAL ; 
 int SPEED_CVT (int) ; 

__attribute__((used)) static int parse_device(tuple_t *tuple, cistpl_device_t *device)
{
	int i;
	u_char scale;
	u_char *p, *q;

	p = (u_char *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	device->ndev = 0;
	for (i = 0; i < CISTPL_MAX_DEVICES; i++) {

		if (*p == 0xff)
			break;
		device->dev[i].type = (*p >> 4);
		device->dev[i].wp = (*p & 0x08) ? 1 : 0;
		switch (*p & 0x07) {
		case 0:
			device->dev[i].speed = 0;
			break;
		case 1:
			device->dev[i].speed = 250;
			break;
		case 2:
			device->dev[i].speed = 200;
			break;
		case 3:
			device->dev[i].speed = 150;
			break;
		case 4:
			device->dev[i].speed = 100;
			break;
		case 7:
			if (++p == q)
				return -EINVAL;
			device->dev[i].speed = SPEED_CVT(*p);
			while (*p & 0x80)
				if (++p == q)
					return -EINVAL;
			break;
		default:
			return -EINVAL;
		}

		if (++p == q)
			return -EINVAL;
		if (*p == 0xff)
			break;
		scale = *p & 7;
		if (scale == 7)
			return -EINVAL;
		device->dev[i].size = ((*p >> 3) + 1) * (512 << (scale*2));
		device->ndev++;
		if (++p == q)
			break;
	}

	return 0;
}