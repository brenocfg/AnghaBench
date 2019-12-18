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
struct atm_vcc {int dummy; } ;
struct atm_qos {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int find_vcc (struct atm_vcc*) ; 
 int /*<<< orphan*/  set_qsb (struct atm_vcc*,struct atm_qos*,int) ; 

__attribute__((used)) static int ppe_change_qos(struct atm_vcc *vcc, struct atm_qos *qos, int flags)
{
	int conn;

	if ( vcc == NULL || qos == NULL )
		return -EINVAL;

	conn = find_vcc(vcc);
	if ( conn < 0 )
		return -EINVAL;

	set_qsb(vcc, qos, conn);

	return 0;
}