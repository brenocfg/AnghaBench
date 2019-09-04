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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hvc_struct {int vtermno; } ;

/* Variables and functions */
 struct hvc_struct* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvc_opal_boot_priv ; 
 int /*<<< orphan*/ ** hvc_opal_privs ; 
 int hvc_remove (struct hvc_struct*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hvc_opal_remove(struct platform_device *dev)
{
	struct hvc_struct *hp = dev_get_drvdata(&dev->dev);
	int rc, termno;

	termno = hp->vtermno;
	rc = hvc_remove(hp);
	if (rc == 0) {
		if (hvc_opal_privs[termno] != &hvc_opal_boot_priv)
			kfree(hvc_opal_privs[termno]);
		hvc_opal_privs[termno] = NULL;
	}
	return rc;
}