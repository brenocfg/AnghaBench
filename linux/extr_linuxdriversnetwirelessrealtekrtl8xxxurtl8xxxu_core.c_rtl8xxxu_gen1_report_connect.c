#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtl8xxxu_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; } ;
struct h2c_cmd {TYPE_1__ joinbss; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_JOIN_BSS_CONNECT ; 
 int /*<<< orphan*/  H2C_JOIN_BSS_DISCONNECT ; 
 int /*<<< orphan*/  H2C_JOIN_BSS_REPORT ; 
 int /*<<< orphan*/  memset (struct h2c_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_gen1_h2c_cmd (struct rtl8xxxu_priv*,struct h2c_cmd*,int) ; 

void rtl8xxxu_gen1_report_connect(struct rtl8xxxu_priv *priv,
				  u8 macid, bool connect)
{
	struct h2c_cmd h2c;

	memset(&h2c, 0, sizeof(struct h2c_cmd));

	h2c.joinbss.cmd = H2C_JOIN_BSS_REPORT;

	if (connect)
		h2c.joinbss.data = H2C_JOIN_BSS_CONNECT;
	else
		h2c.joinbss.data = H2C_JOIN_BSS_DISCONNECT;

	rtl8xxxu_gen1_h2c_cmd(priv, &h2c, sizeof(h2c.joinbss));
}