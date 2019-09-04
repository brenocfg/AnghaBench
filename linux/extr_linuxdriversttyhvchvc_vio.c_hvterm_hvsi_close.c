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
struct hvterm_priv {int /*<<< orphan*/  hvsi; int /*<<< orphan*/  termno; } ;
struct hvc_struct {size_t vtermno; } ;

/* Variables and functions */
 int /*<<< orphan*/  hvsilib_close (int /*<<< orphan*/ *,struct hvc_struct*) ; 
 struct hvterm_priv** hvterm_privs ; 
 int /*<<< orphan*/  notifier_del_irq (struct hvc_struct*,int) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hvterm_hvsi_close(struct hvc_struct *hp, int data)
{
	struct hvterm_priv *pv = hvterm_privs[hp->vtermno];

	pr_devel("HVSI@%x: do close !\n", pv->termno);

	hvsilib_close(&pv->hvsi, hp);

	notifier_del_irq(hp, data);
}