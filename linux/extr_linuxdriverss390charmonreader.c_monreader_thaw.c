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
struct mon_private {int /*<<< orphan*/  iucv_severed; int /*<<< orphan*/ * path; int /*<<< orphan*/  iucv_connected; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IUCV_IPRMDATA ; 
 int /*<<< orphan*/  MON_MSGLIM ; 
 int /*<<< orphan*/  MON_SERVICE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct mon_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * iucv_path_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iucv_path_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mon_private*) ; 
 int /*<<< orphan*/  iucv_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mon_conn_wait_queue ; 
 int /*<<< orphan*/  monreader_iucv_handler ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  user_data_connect ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int monreader_thaw(struct device *dev)
{
	struct mon_private *monpriv = dev_get_drvdata(dev);
	int rc;

	if (!monpriv)
		return 0;
	rc = -ENOMEM;
	monpriv->path = iucv_path_alloc(MON_MSGLIM, IUCV_IPRMDATA, GFP_KERNEL);
	if (!monpriv->path)
		goto out;
	rc = iucv_path_connect(monpriv->path, &monreader_iucv_handler,
			       MON_SERVICE, NULL, user_data_connect, monpriv);
	if (rc) {
		pr_err("Connecting to the z/VM *MONITOR system service "
		       "failed with rc=%i\n", rc);
		goto out_path;
	}
	wait_event(mon_conn_wait_queue,
		   atomic_read(&monpriv->iucv_connected) ||
		   atomic_read(&monpriv->iucv_severed));
	if (atomic_read(&monpriv->iucv_severed))
		goto out_path;
	return 0;
out_path:
	rc = -EIO;
	iucv_path_free(monpriv->path);
	monpriv->path = NULL;
out:
	atomic_set(&monpriv->iucv_severed, 1);
	return rc;
}