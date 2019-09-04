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
struct mp_priv {int dummy; } ;
struct _adapter {struct mp_priv mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_mp_priv (struct mp_priv*) ; 

void mp871xdeinit(struct _adapter *padapter)
{
	struct mp_priv *pmppriv = &padapter->mppriv;

	free_mp_priv(pmppriv);
}