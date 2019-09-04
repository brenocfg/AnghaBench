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
typedef  int u16 ;
struct lbs_private {scalar_t__ card; } ;
struct if_cs_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IF_CS_BIT_TX ; 
 int /*<<< orphan*/  IF_CS_CARD_STATUS ; 
 int /*<<< orphan*/  IF_CS_HOST_INT_CAUSE ; 
 int /*<<< orphan*/  IF_CS_HOST_STATUS ; 
 int /*<<< orphan*/  IF_CS_WRITE ; 
 int /*<<< orphan*/  IF_CS_WRITE_LEN ; 
 int /*<<< orphan*/  if_cs_disable_ints (struct if_cs_card*) ; 
 int /*<<< orphan*/  if_cs_enable_ints (struct if_cs_card*) ; 
 int if_cs_read16 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_write16 (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_cs_write16_rep (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_cs_write8 (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void if_cs_send_data(struct lbs_private *priv, u8 *buf, u16 nb)
{
	struct if_cs_card *card = (struct if_cs_card *)priv->card;
	u16 status;

	if_cs_disable_ints(card);

	status = if_cs_read16(card, IF_CS_CARD_STATUS);
	BUG_ON((status & IF_CS_BIT_TX) == 0);

	if_cs_write16(card, IF_CS_WRITE_LEN, nb);

	/* write even number of bytes, then odd byte if necessary */
	if_cs_write16_rep(card, IF_CS_WRITE, buf, nb / 2);
	if (nb & 1)
		if_cs_write8(card, IF_CS_WRITE, buf[nb-1]);

	if_cs_write16(card, IF_CS_HOST_STATUS, IF_CS_BIT_TX);
	if_cs_write16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_TX);
	if_cs_enable_ints(card);
}