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
struct hvc_struct {size_t vtermno; } ;
struct hvc_opal_priv {int /*<<< orphan*/  hvsi; } ;

/* Variables and functions */
 struct hvc_opal_priv** hvc_opal_privs ; 
 int hvsilib_open (int /*<<< orphan*/ *,struct hvc_struct*) ; 
 int notifier_add_irq (struct hvc_struct*,int) ; 
 int /*<<< orphan*/  pr_devel (char*,size_t) ; 

__attribute__((used)) static int hvc_opal_hvsi_open(struct hvc_struct *hp, int data)
{
	struct hvc_opal_priv *pv = hvc_opal_privs[hp->vtermno];
	int rc;

	pr_devel("HVSI@%x: do open !\n", hp->vtermno);

	rc = notifier_add_irq(hp, data);
	if (rc)
		return rc;

	return hvsilib_open(&pv->hvsi, hp);
}