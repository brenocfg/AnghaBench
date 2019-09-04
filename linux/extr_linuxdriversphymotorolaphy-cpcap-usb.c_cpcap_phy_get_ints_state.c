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
struct cpcap_usb_ints_state {int id_ground; int id_float; int vbusov; int vbusvld; int sessvld; int sessend; int se1; int dm; int dp; } ;
struct cpcap_phy_ddata {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CPCAP_REG_INTS1 ; 
 int /*<<< orphan*/  CPCAP_REG_INTS2 ; 
 int /*<<< orphan*/  CPCAP_REG_INTS4 ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int cpcap_phy_get_ints_state(struct cpcap_phy_ddata *ddata,
				    struct cpcap_usb_ints_state *s)
{
	int val, error;

	error = regmap_read(ddata->reg, CPCAP_REG_INTS1, &val);
	if (error)
		return error;

	s->id_ground = val & BIT(15);
	s->id_float = val & BIT(14);
	s->vbusov = val & BIT(11);

	error = regmap_read(ddata->reg, CPCAP_REG_INTS2, &val);
	if (error)
		return error;

	s->vbusvld = val & BIT(3);
	s->sessvld = val & BIT(2);
	s->sessend = val & BIT(1);
	s->se1 = val & BIT(0);

	error = regmap_read(ddata->reg, CPCAP_REG_INTS4, &val);
	if (error)
		return error;

	s->dm = val & BIT(1);
	s->dp = val & BIT(0);

	return 0;
}