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
typedef  int /*<<< orphan*/  u8 ;
struct ipw_priv {scalar_t__ eeprom; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_TRACE (char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_read_u16 (struct ipw_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_read_eeprom(struct ipw_priv *priv)
{
	int i;
	__le16 *eeprom = (__le16 *) priv->eeprom;

	IPW_DEBUG_TRACE(">>\n");

	/* read entire contents of eeprom into private buffer */
	for (i = 0; i < 128; i++)
		eeprom[i] = cpu_to_le16(eeprom_read_u16(priv, (u8) i));

	IPW_DEBUG_TRACE("<<\n");
}