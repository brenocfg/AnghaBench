#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zoran {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  hdl; int /*<<< orphan*/  video_dev; TYPE_2__* pci_dev; int /*<<< orphan*/  zr36057_mem; struct zoran* stat_com; TYPE_1__* vfe; TYPE_1__* codec; int /*<<< orphan*/  initialized; } ;
struct videocodec_master {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  hdl; int /*<<< orphan*/  video_dev; TYPE_2__* pci_dev; int /*<<< orphan*/  zr36057_mem; struct videocodec_master* stat_com; TYPE_1__* vfe; TYPE_1__* codec; int /*<<< orphan*/  initialized; } ;
struct v4l2_device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {struct zoran* master_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR36057_SPGPPCR ; 
 int /*<<< orphan*/  btwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct zoran*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct zoran*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_2__*) ; 
 struct zoran* to_zoran (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videocodec_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  zoran_proc_cleanup (struct zoran*) ; 
 int /*<<< orphan*/  zoran_set_pci_master (struct zoran*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zoran_unregister_i2c (struct zoran*) ; 

__attribute__((used)) static void zoran_remove(struct pci_dev *pdev)
{
	struct v4l2_device *v4l2_dev = dev_get_drvdata(&pdev->dev);
	struct zoran *zr = to_zoran(v4l2_dev);

	if (!zr->initialized)
		goto exit_free;

	/* unregister videocodec bus */
	if (zr->codec) {
		struct videocodec_master *master = zr->codec->master_data;

		videocodec_detach(zr->codec);
		kfree(master);
	}
	if (zr->vfe) {
		struct videocodec_master *master = zr->vfe->master_data;

		videocodec_detach(zr->vfe);
		kfree(master);
	}

	/* unregister i2c bus */
	zoran_unregister_i2c(zr);
	/* disable PCI bus-mastering */
	zoran_set_pci_master(zr, 0);
	/* put chip into reset */
	btwrite(0, ZR36057_SPGPPCR);
	free_irq(zr->pci_dev->irq, zr);
	/* unmap and free memory */
	kfree(zr->stat_com);
	zoran_proc_cleanup(zr);
	iounmap(zr->zr36057_mem);
	pci_disable_device(zr->pci_dev);
	video_unregister_device(zr->video_dev);
exit_free:
	v4l2_ctrl_handler_free(&zr->hdl);
	v4l2_device_unregister(&zr->v4l2_dev);
	kfree(zr);
}