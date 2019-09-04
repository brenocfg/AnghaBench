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
struct _adapter {int dummy; } ;

/* Variables and functions */
 int _init_mlme_priv (struct _adapter*) ; 

int r8712_init_mlme_priv(struct _adapter *padapter)
{
	return _init_mlme_priv(padapter);
}