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
struct cmd_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _free_cmd_priv (struct cmd_priv*) ; 

void r8712_free_cmd_priv(struct cmd_priv *pcmdpriv)
{
	_free_cmd_priv(pcmdpriv);
}