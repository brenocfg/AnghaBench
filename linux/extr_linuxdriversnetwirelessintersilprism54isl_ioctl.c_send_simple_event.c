#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* pointer; int length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndev; } ;
typedef  TYPE_2__ islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWEVCUSTOM ; 
 int IW_CUSTOM_MAX ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,char*) ; 

__attribute__((used)) static void
send_simple_event(islpci_private *priv, const char *str)
{
	union iwreq_data wrqu;
	char *memptr;
	int n = strlen(str);

	memptr = kmalloc(IW_CUSTOM_MAX, GFP_KERNEL);
	if (!memptr)
		return;
	BUG_ON(n >= IW_CUSTOM_MAX);
	wrqu.data.pointer = memptr;
	wrqu.data.length = n;
	strcpy(memptr, str);
	wireless_send_event(priv->ndev, IWEVCUSTOM, &wrqu, memptr);
	kfree(memptr);
}