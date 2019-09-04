#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_5__ {int TupleDataLen; scalar_t__ TupleData; } ;
typedef  TYPE_1__ tuple_t ;
struct TYPE_6__ {int last_idx; int subtuples; scalar_t__* rmask; scalar_t__ base; } ;
typedef  TYPE_2__ cistpl_config_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int parse_config(tuple_t *tuple, cistpl_config_t *config)
{
	int rasz, rmsz, i;
	u_char *p;

	p = (u_char *)tuple->TupleData;
	rasz = *p & 0x03;
	rmsz = (*p & 0x3c) >> 2;
	if (tuple->TupleDataLen < rasz+rmsz+4)
		return -EINVAL;
	config->last_idx = *(++p);
	p++;
	config->base = 0;
	for (i = 0; i <= rasz; i++)
		config->base += p[i] << (8*i);
	p += rasz+1;
	for (i = 0; i < 4; i++)
		config->rmask[i] = 0;
	for (i = 0; i <= rmsz; i++)
		config->rmask[i>>2] += p[i] << (8*(i%4));
	config->subtuples = tuple->TupleDataLen - (rasz+rmsz+4);
	return 0;
}