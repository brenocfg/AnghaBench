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
struct TYPE_3__ {int dcr; int ecr; } ;
struct TYPE_4__ {TYPE_1__ ip32; } ;
struct parport_state {TYPE_2__ u; } ;
struct pardevice {int dummy; } ;

/* Variables and functions */
 int DCR_SELECT ; 
 int DCR_nINIT ; 
 int ECR_MODE_PS2 ; 
 int ECR_SERVINTR ; 
 int ECR_nERRINTR ; 

__attribute__((used)) static void parport_ip32_init_state(struct pardevice *dev,
				    struct parport_state *s)
{
	s->u.ip32.dcr = DCR_SELECT | DCR_nINIT;
	s->u.ip32.ecr = ECR_MODE_PS2 | ECR_nERRINTR | ECR_SERVINTR;
}