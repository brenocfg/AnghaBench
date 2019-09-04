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
typedef  int u16 ;
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RETRY_LIMIT ; 
 int RETRY_LIMIT_LONG_MASK ; 
 int RETRY_LIMIT_LONG_SHIFT ; 
 int RETRY_LIMIT_SHORT_MASK ; 
 int RETRY_LIMIT_SHORT_SHIFT ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rtl8xxxu_set_retry(struct rtl8xxxu_priv *priv, u16 short_retry, u16 long_retry)
{
	u16 val16;

	val16 = ((short_retry << RETRY_LIMIT_SHORT_SHIFT) &
		 RETRY_LIMIT_SHORT_MASK) |
		((long_retry << RETRY_LIMIT_LONG_SHIFT) &
		 RETRY_LIMIT_LONG_MASK);

	rtl8xxxu_write16(priv, REG_RETRY_LIMIT, val16);
}