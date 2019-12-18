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
struct nfc_llc {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* stop ) (struct nfc_llc*) ;} ;

/* Variables and functions */
 int stub1 (struct nfc_llc*) ; 

int nfc_llc_stop(struct nfc_llc *llc)
{
	return llc->ops->stop(llc);
}