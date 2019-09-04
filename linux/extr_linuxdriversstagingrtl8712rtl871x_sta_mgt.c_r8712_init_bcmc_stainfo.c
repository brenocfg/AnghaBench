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
struct sta_priv {int dummy; } ;
struct _adapter {struct sta_priv stapriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_alloc_stainfo (struct sta_priv*,unsigned char*) ; 

void r8712_init_bcmc_stainfo(struct _adapter *padapter)
{
	unsigned char bcast_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	struct	sta_priv *pstapriv = &padapter->stapriv;

	r8712_alloc_stainfo(pstapriv, bcast_addr);
}