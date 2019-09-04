#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int reg_offset; int /*<<< orphan*/  base; TYPE_4__* platformdev; } ;
struct TYPE_12__ {int common_irq_installed; int /*<<< orphan*/  core_if; int /*<<< orphan*/ * hcd; int /*<<< orphan*/ * pcd; TYPE_1__ os_dep; } ;
typedef  TYPE_2__ dwc_otg_device_t ;
struct TYPE_13__ {int irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CIL ; 
 int /*<<< orphan*/  DBG_HCDV ; 
 TYPE_2__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_ERROR (char*,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 TYPE_4__* _dev ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dwc_otg_adp_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_attr_create (TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_otg_cil_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_common_irq ; 
 int /*<<< orphan*/  dwc_otg_core_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_disable_global_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_driver_remove (TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_otg_enable_global_interrupts (int /*<<< orphan*/ ) ; 
 int dwc_otg_get_gsnpsid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_get_param_adp_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_is_host_mode (int /*<<< orphan*/ ) ; 
 int hcd_init (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int pcd_init (TYPE_4__*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 scalar_t__ set_parameters (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc_otg_driver_probe(
#ifdef LM_INTERFACE
				       struct lm_device *_dev
#elif defined(PCI_INTERFACE)
				       struct pci_dev *_dev,
				       const struct pci_device_id *id
#elif  defined(PLATFORM_INTERFACE)
                                       struct platform_device *_dev
#endif
    )
{
	int retval = 0;
	dwc_otg_device_t *dwc_otg_device;
        int devirq;

	dev_dbg(&_dev->dev, "dwc_otg_driver_probe(%p)\n", _dev);
#ifdef LM_INTERFACE
	dev_dbg(&_dev->dev, "start=0x%08x\n", (unsigned)_dev->resource.start);
#elif defined(PCI_INTERFACE)
	if (!id) {
		DWC_ERROR("Invalid pci_device_id %p", id);
		return -EINVAL;
	}

	if (!_dev || (pci_enable_device(_dev) < 0)) {
		DWC_ERROR("Invalid pci_device %p", _dev);
		return -ENODEV;
	}
	dev_dbg(&_dev->dev, "start=0x%08x\n", (unsigned)pci_resource_start(_dev,0));
	/* other stuff needed as well? */

#elif  defined(PLATFORM_INTERFACE)
	dev_dbg(&_dev->dev, "start=0x%08x (len 0x%x)\n",
                (unsigned)_dev->resource->start,
                (unsigned)(_dev->resource->end - _dev->resource->start));
#endif

	dwc_otg_device = DWC_ALLOC(sizeof(dwc_otg_device_t));

	if (!dwc_otg_device) {
		dev_err(&_dev->dev, "kmalloc of dwc_otg_device failed\n");
		return -ENOMEM;
	}

	memset(dwc_otg_device, 0, sizeof(*dwc_otg_device));
	dwc_otg_device->os_dep.reg_offset = 0xFFFFFFFF;
	dwc_otg_device->os_dep.platformdev = _dev;

	/*
	 * Map the DWC_otg Core memory into virtual address space.
	 */
#ifdef LM_INTERFACE
	dwc_otg_device->os_dep.base = ioremap(_dev->resource.start, SZ_256K);

	if (!dwc_otg_device->os_dep.base) {
		dev_err(&_dev->dev, "ioremap() failed\n");
		DWC_FREE(dwc_otg_device);
		return -ENOMEM;
	}
	dev_dbg(&_dev->dev, "base=0x%08x\n",
		(unsigned)dwc_otg_device->os_dep.base);
#elif defined(PCI_INTERFACE)
	_dev->current_state = PCI_D0;
	_dev->dev.power.power_state = PMSG_ON;

	if (!_dev->irq) {
		DWC_ERROR("Found HC with no IRQ. Check BIOS/PCI %s setup!",
			  pci_name(_dev));
		iounmap(dwc_otg_device->os_dep.base);
		DWC_FREE(dwc_otg_device);
		return -ENODEV;
	}

	dwc_otg_device->os_dep.rsrc_start = pci_resource_start(_dev, 0);
	dwc_otg_device->os_dep.rsrc_len = pci_resource_len(_dev, 0);
	DWC_DEBUGPL(DBG_ANY, "PCI resource: start=%08x, len=%08x\n",
		    (unsigned)dwc_otg_device->os_dep.rsrc_start,
		    (unsigned)dwc_otg_device->os_dep.rsrc_len);
	if (!request_mem_region
	    (dwc_otg_device->os_dep.rsrc_start, dwc_otg_device->os_dep.rsrc_len,
	     "dwc_otg")) {
		dev_dbg(&_dev->dev, "error requesting memory\n");
		iounmap(dwc_otg_device->os_dep.base);
		DWC_FREE(dwc_otg_device);
		return -EFAULT;
	}

	dwc_otg_device->os_dep.base =
	    ioremap_nocache(dwc_otg_device->os_dep.rsrc_start,
			    dwc_otg_device->os_dep.rsrc_len);
	if (dwc_otg_device->os_dep.base == NULL) {
		dev_dbg(&_dev->dev, "error mapping memory\n");
		release_mem_region(dwc_otg_device->os_dep.rsrc_start,
				   dwc_otg_device->os_dep.rsrc_len);
		iounmap(dwc_otg_device->os_dep.base);
		DWC_FREE(dwc_otg_device);
		return -EFAULT;
	}
	dev_dbg(&_dev->dev, "base=0x%p (before adjust) \n",
		dwc_otg_device->os_dep.base);
	dwc_otg_device->os_dep.base = (char *)dwc_otg_device->os_dep.base;
	dev_dbg(&_dev->dev, "base=0x%p (after adjust) \n",
		dwc_otg_device->os_dep.base);
	dev_dbg(&_dev->dev, "%s: mapped PA 0x%x to VA 0x%p\n", __func__,
		(unsigned)dwc_otg_device->os_dep.rsrc_start,
		dwc_otg_device->os_dep.base);

	pci_set_master(_dev);
	pci_set_drvdata(_dev, dwc_otg_device);
#elif defined(PLATFORM_INTERFACE)
        DWC_DEBUGPL(DBG_ANY,"Platform resource: start=%08x, len=%08x\n",
                    _dev->resource->start,
                    _dev->resource->end - _dev->resource->start + 1);
#if 1
        if (!request_mem_region(_dev->resource[0].start,
                                _dev->resource[0].end - _dev->resource[0].start + 1,
                                "dwc_otg")) {
          dev_dbg(&_dev->dev, "error reserving mapped memory\n");
          retval = -EFAULT;
          goto fail;
        }

	dwc_otg_device->os_dep.base = ioremap_nocache(_dev->resource[0].start,
                                                      _dev->resource[0].end -
                                                      _dev->resource[0].start+1);
	if (fiq_enable)
	{
		if (!request_mem_region(_dev->resource[1].start,
	                                _dev->resource[1].end - _dev->resource[1].start + 1,
	                                "dwc_otg")) {
	          dev_dbg(&_dev->dev, "error reserving mapped memory\n");
	          retval = -EFAULT;
	          goto fail;
	}

		dwc_otg_device->os_dep.mphi_base = ioremap_nocache(_dev->resource[1].start,
							    _dev->resource[1].end -
							    _dev->resource[1].start + 1);
	}

#else
        {
                struct map_desc desc = {
                    .virtual = IO_ADDRESS((unsigned)_dev->resource->start),
                    .pfn     = __phys_to_pfn((unsigned)_dev->resource->start),
                    .length  = SZ_128K,
                    .type    = MT_DEVICE
                };
                iotable_init(&desc, 1);
                dwc_otg_device->os_dep.base = (void *)desc.virtual;
        }
#endif
	if (!dwc_otg_device->os_dep.base) {
		dev_err(&_dev->dev, "ioremap() failed\n");
		retval = -ENOMEM;
		goto fail;
	}
	dev_info(&_dev->dev, "base=%p\n", dwc_otg_device->os_dep.base);
#endif

	/*
	 * Initialize driver data to point to the global DWC_otg
	 * Device structure.
	 */
#ifdef LM_INTERFACE
	lm_set_drvdata(_dev, dwc_otg_device);
#elif defined(PLATFORM_INTERFACE)
	platform_set_drvdata(_dev, dwc_otg_device);
#endif
	dev_dbg(&_dev->dev, "dwc_otg_device=0x%p\n", dwc_otg_device);

	dwc_otg_device->core_if = dwc_otg_cil_init(dwc_otg_device->os_dep.base);
        DWC_DEBUGPL(DBG_HCDV, "probe of device %p given core_if %p\n",
                    dwc_otg_device, dwc_otg_device->core_if);//GRAYG

	if (!dwc_otg_device->core_if) {
		dev_err(&_dev->dev, "CIL initialization failed!\n");
		retval = -ENOMEM;
		goto fail;
	}

	dev_dbg(&_dev->dev, "Calling get_gsnpsid\n");
	/*
	 * Attempt to ensure this device is really a DWC_otg Controller.
	 * Read and verify the SNPSID register contents. The value should be
	 * 0x45F42XXX or 0x45F42XXX, which corresponds to either "OT2" or "OTG3",
	 * as in "OTG version 2.XX" or "OTG version 3.XX".
	 */

	if (((dwc_otg_get_gsnpsid(dwc_otg_device->core_if) & 0xFFFFF000) !=	0x4F542000) &&
		((dwc_otg_get_gsnpsid(dwc_otg_device->core_if) & 0xFFFFF000) != 0x4F543000)) {
		dev_err(&_dev->dev, "Bad value for SNPSID: 0x%08x\n",
			dwc_otg_get_gsnpsid(dwc_otg_device->core_if));
		retval = -EINVAL;
		goto fail;
	}

	/*
	 * Validate parameter values.
	 */
	dev_dbg(&_dev->dev, "Calling set_parameters\n");
	if (set_parameters(dwc_otg_device->core_if)) {
		retval = -EINVAL;
		goto fail;
	}

	/*
	 * Create Device Attributes in sysfs
	 */
	dev_dbg(&_dev->dev, "Calling attr_create\n");
	dwc_otg_attr_create(_dev);

	/*
	 * Disable the global interrupt until all the interrupt
	 * handlers are installed.
	 */
	dev_dbg(&_dev->dev, "Calling disable_global_interrupts\n");
	dwc_otg_disable_global_interrupts(dwc_otg_device->core_if);

	/*
	 * Install the interrupt handler for the common interrupts before
	 * enabling common interrupts in core_init below.
	 */

#if defined(PLATFORM_INTERFACE)
	devirq = platform_get_irq(_dev, fiq_enable ? 0 : 1);
#else
	devirq = _dev->irq;
#endif
	DWC_DEBUGPL(DBG_CIL, "registering (common) handler for irq%d\n",
		    devirq);
	dev_dbg(&_dev->dev, "Calling request_irq(%d)\n", devirq);
	retval = request_irq(devirq, dwc_otg_common_irq,
                             IRQF_SHARED,
                             "dwc_otg", dwc_otg_device);
	if (retval) {
		DWC_ERROR("request of irq%d failed\n", devirq);
		retval = -EBUSY;
		goto fail;
	} else {
		dwc_otg_device->common_irq_installed = 1;
	}

#ifndef IRQF_TRIGGER_LOW
#if defined(LM_INTERFACE) || defined(PLATFORM_INTERFACE)
	dev_dbg(&_dev->dev, "Calling set_irq_type\n");
	set_irq_type(devirq,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30))
                     IRQT_LOW
#else
                     IRQ_TYPE_LEVEL_LOW
#endif
                    );
#endif
#endif /*IRQF_TRIGGER_LOW*/

	/*
	 * Initialize the DWC_otg core.
	 */
	dev_dbg(&_dev->dev, "Calling dwc_otg_core_init\n");
	dwc_otg_core_init(dwc_otg_device->core_if);

#ifndef DWC_HOST_ONLY
	/*
	 * Initialize the PCD
	 */
	dev_dbg(&_dev->dev, "Calling pcd_init\n");
	retval = pcd_init(_dev);
	if (retval != 0) {
		DWC_ERROR("pcd_init failed\n");
		dwc_otg_device->pcd = NULL;
		goto fail;
	}
#endif
#ifndef DWC_DEVICE_ONLY
	/*
	 * Initialize the HCD
	 */
	dev_dbg(&_dev->dev, "Calling hcd_init\n");
	retval = hcd_init(_dev);
	if (retval != 0) {
		DWC_ERROR("hcd_init failed\n");
		dwc_otg_device->hcd = NULL;
		goto fail;
	}
#endif
        /* Recover from drvdata having been overwritten by hcd_init() */
#ifdef LM_INTERFACE
	lm_set_drvdata(_dev, dwc_otg_device);
#elif defined(PLATFORM_INTERFACE)
	platform_set_drvdata(_dev, dwc_otg_device);
#elif defined(PCI_INTERFACE)
	pci_set_drvdata(_dev, dwc_otg_device);
	dwc_otg_device->os_dep.pcidev = _dev;
#endif

	/*
	 * Enable the global interrupt after all the interrupt
	 * handlers are installed if there is no ADP support else
	 * perform initial actions required for Internal ADP logic.
	 */
	if (!dwc_otg_get_param_adp_enable(dwc_otg_device->core_if)) {
	        dev_dbg(&_dev->dev, "Calling enable_global_interrupts\n");
		dwc_otg_enable_global_interrupts(dwc_otg_device->core_if);
	        dev_dbg(&_dev->dev, "Done\n");
	} else
		dwc_otg_adp_start(dwc_otg_device->core_if,
							dwc_otg_is_host_mode(dwc_otg_device->core_if));

	return 0;

fail:
	dwc_otg_driver_remove(_dev);
	return retval;
}