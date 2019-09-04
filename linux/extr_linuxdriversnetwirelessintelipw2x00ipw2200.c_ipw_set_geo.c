#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipw_priv {int /*<<< orphan*/  ieee; int /*<<< orphan*/ * eeprom; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 size_t EEPROM_COUNTRY_CODE ; 
 int /*<<< orphan*/  IPW_WARNING (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ipw_geos ; 
 int /*<<< orphan*/  libipw_set_geo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ipw_set_geo(struct ipw_priv *priv)
{
	int j;

	for (j = 0; j < ARRAY_SIZE(ipw_geos); j++) {
		if (!memcmp(&priv->eeprom[EEPROM_COUNTRY_CODE],
			    ipw_geos[j].name, 3))
			break;
	}

	if (j == ARRAY_SIZE(ipw_geos)) {
		IPW_WARNING("SKU [%c%c%c] not recognized.\n",
			    priv->eeprom[EEPROM_COUNTRY_CODE + 0],
			    priv->eeprom[EEPROM_COUNTRY_CODE + 1],
			    priv->eeprom[EEPROM_COUNTRY_CODE + 2]);
		j = 0;
	}

	libipw_set_geo(priv->ieee, &ipw_geos[j]);
}