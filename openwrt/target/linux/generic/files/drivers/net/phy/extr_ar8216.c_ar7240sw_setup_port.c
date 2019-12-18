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
typedef  int /*<<< orphan*/  u32 ;
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 void __ar8216_setup_port (struct ar8xxx_priv*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar7240sw_setup_port(struct ar8xxx_priv *priv, int port, u32 members)
{
	return __ar8216_setup_port(priv, port, members, false);
}