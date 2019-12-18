#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ valcrc; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ qoperand; } ;
struct TYPE_8__ {int size; } ;
typedef  unsigned int TSQuerySign ;
typedef  TYPE_2__* TSQuery ;
typedef  TYPE_3__ QueryItem ;

/* Variables and functions */
 TYPE_3__* GETQUERY (TYPE_2__*) ; 
 scalar_t__ QI_VAL ; 
 unsigned int TSQS_SIGLEN ; 

TSQuerySign
makeTSQuerySign(TSQuery a)
{
	int			i;
	QueryItem  *ptr = GETQUERY(a);
	TSQuerySign sign = 0;

	for (i = 0; i < a->size; i++)
	{
		if (ptr->type == QI_VAL)
			sign |= ((TSQuerySign) 1) << (((unsigned int) ptr->qoperand.valcrc) % TSQS_SIGLEN);
		ptr++;
	}

	return sign;
}