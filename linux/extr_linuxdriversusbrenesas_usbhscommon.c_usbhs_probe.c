#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
struct TYPE_18__ {int type; int pio_dma_border; scalar_t__ enable_gpio; scalar_t__ get_vbus; int /*<<< orphan*/  pipe_size; scalar_t__ pipe_configs; int /*<<< orphan*/  notifier; } ;
struct TYPE_17__ {int /*<<< orphan*/  notifier_call; } ;
struct usbhs_priv {TYPE_1__ dparam; int /*<<< orphan*/  notify_hotplug_work; struct platform_device* pdev; int /*<<< orphan*/  irqflags; int /*<<< orphan*/  irq; TYPE_1__ pfunc; TYPE_13__ nb; int /*<<< orphan*/  edev; int /*<<< orphan*/  base; } ;
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct renesas_usbhs_driver_callback {int /*<<< orphan*/  (* notify_hotplug ) (struct platform_device*) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  get_id; } ;
struct renesas_usbhs_platform_info {struct renesas_usbhs_driver_callback driver_callback; TYPE_8__ platform_callback; TYPE_8__ driver_param; } ;
struct renesas_usbhs_platform_callback {int dummy; } ;
struct renesas_usbhs_driver_param {int dummy; } ;
struct TYPE_19__ {scalar_t__ of_node; struct renesas_usbhs_platform_info* platform_data; } ;
struct platform_device {TYPE_5__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int IORESOURCE_IRQ_SHAREABLE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBHSF_RUNTIME_PWCTRL ; 
#define  USBHS_TYPE_RCAR_GEN2 131 
#define  USBHS_TYPE_RCAR_GEN3 130 
#define  USBHS_TYPE_RCAR_GEN3_WITH_PLL 129 
#define  USBHS_TYPE_RZA1 128 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_5__*,char*,scalar_t__) ; 
 int devm_extcon_register_notifier (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_5__*,struct resource*) ; 
 struct usbhs_priv* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extcon_get_edev_by_phandle (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  gpio_get_value (scalar_t__) ; 
 int /*<<< orphan*/  gpio_request_one (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hardware_init ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_8__*,int) ; 
 scalar_t__ of_property_read_bool (scalar_t__,char*) ; 
 int /*<<< orphan*/  phy_reset ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usbhs_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_5__*) ; 
 struct renesas_usbhs_platform_info* renesas_usbhs_get_info (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ ) ; 
 int usbhs_fifo_probe (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_fifo_remove (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_mod_autonomy_mode (struct usbhs_priv*) ; 
 int usbhs_mod_probe (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_mod_remove (struct usbhs_priv*) ; 
 struct renesas_usbhs_platform_info* usbhs_parse_dt (TYPE_5__*) ; 
 int usbhs_pipe_probe (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_pipe_remove (struct usbhs_priv*) ; 
 int usbhs_platform_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  usbhs_priv_to_lock (struct usbhs_priv*) ; 
 TYPE_1__ usbhs_rcar2_ops ; 
 TYPE_1__ usbhs_rcar3_ops ; 
 TYPE_1__ usbhs_rcar3_with_pll_ops ; 
 TYPE_1__ usbhs_rza1_ops ; 
 int /*<<< orphan*/  usbhs_sys_clock_ctrl (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbhsc_default_pipe ; 
 int /*<<< orphan*/  usbhsc_drvcllbck_notify_hotplug (struct platform_device*) ; 
 int /*<<< orphan*/  usbhsc_flags_has (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsc_flags_set (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsc_notify_hotplug ; 
 int /*<<< orphan*/  usbhsc_power_ctrl (struct usbhs_priv*,int) ; 

__attribute__((used)) static int usbhs_probe(struct platform_device *pdev)
{
	struct renesas_usbhs_platform_info *info = renesas_usbhs_get_info(pdev);
	struct renesas_usbhs_driver_callback *dfunc;
	struct usbhs_priv *priv;
	struct resource *res, *irq_res;
	int ret;

	/* check device node */
	if (pdev->dev.of_node)
		info = pdev->dev.platform_data = usbhs_parse_dt(&pdev->dev);

	/* check platform information */
	if (!info) {
		dev_err(&pdev->dev, "no platform information\n");
		return -EINVAL;
	}

	/* platform data */
	irq_res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq_res) {
		dev_err(&pdev->dev, "Not enough Renesas USB platform resources.\n");
		return -ENODEV;
	}

	/* usb private data */
	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	if (of_property_read_bool(pdev->dev.of_node, "extcon")) {
		priv->edev = extcon_get_edev_by_phandle(&pdev->dev, 0);
		if (IS_ERR(priv->edev))
			return PTR_ERR(priv->edev);
	}

	/*
	 * care platform info
	 */

	memcpy(&priv->dparam,
	       &info->driver_param,
	       sizeof(struct renesas_usbhs_driver_param));

	switch (priv->dparam.type) {
	case USBHS_TYPE_RCAR_GEN2:
		priv->pfunc = usbhs_rcar2_ops;
		break;
	case USBHS_TYPE_RCAR_GEN3:
		priv->pfunc = usbhs_rcar3_ops;
		break;
	case USBHS_TYPE_RCAR_GEN3_WITH_PLL:
		priv->pfunc = usbhs_rcar3_with_pll_ops;
		if (!IS_ERR_OR_NULL(priv->edev)) {
			priv->nb.notifier_call = priv->pfunc.notifier;
			ret = devm_extcon_register_notifier(&pdev->dev,
							    priv->edev,
							    EXTCON_USB_HOST,
							    &priv->nb);
			if (ret < 0)
				dev_err(&pdev->dev, "no notifier registered\n");
		}
		break;
	case USBHS_TYPE_RZA1:
		priv->pfunc = usbhs_rza1_ops;
		break;
	default:
		if (!info->platform_callback.get_id) {
			dev_err(&pdev->dev, "no platform callbacks");
			return -EINVAL;
		}
		memcpy(&priv->pfunc,
		       &info->platform_callback,
		       sizeof(struct renesas_usbhs_platform_callback));
		break;
	}

	/* set driver callback functions for platform */
	dfunc			= &info->driver_callback;
	dfunc->notify_hotplug	= usbhsc_drvcllbck_notify_hotplug;

	/* set default param if platform doesn't have */
	if (!priv->dparam.pipe_configs) {
		priv->dparam.pipe_configs = usbhsc_default_pipe;
		priv->dparam.pipe_size = ARRAY_SIZE(usbhsc_default_pipe);
	}
	if (!priv->dparam.pio_dma_border)
		priv->dparam.pio_dma_border = 64; /* 64byte */

	/* FIXME */
	/* runtime power control ? */
	if (priv->pfunc.get_vbus)
		usbhsc_flags_set(priv, USBHSF_RUNTIME_PWCTRL);

	/*
	 * priv settings
	 */
	priv->irq	= irq_res->start;
	if (irq_res->flags & IORESOURCE_IRQ_SHAREABLE)
		priv->irqflags = IRQF_SHARED;
	priv->pdev	= pdev;
	INIT_DELAYED_WORK(&priv->notify_hotplug_work, usbhsc_notify_hotplug);
	spin_lock_init(usbhs_priv_to_lock(priv));

	/* call pipe and module init */
	ret = usbhs_pipe_probe(priv);
	if (ret < 0)
		return ret;

	ret = usbhs_fifo_probe(priv);
	if (ret < 0)
		goto probe_end_pipe_exit;

	ret = usbhs_mod_probe(priv);
	if (ret < 0)
		goto probe_end_fifo_exit;

	/* dev_set_drvdata should be called after usbhs_mod_init */
	platform_set_drvdata(pdev, priv);

	/*
	 * deviece reset here because
	 * USB device might be used in boot loader.
	 */
	usbhs_sys_clock_ctrl(priv, 0);

	/* check GPIO determining if USB function should be enabled */
	if (priv->dparam.enable_gpio) {
		gpio_request_one(priv->dparam.enable_gpio, GPIOF_IN, NULL);
		ret = !gpio_get_value(priv->dparam.enable_gpio);
		gpio_free(priv->dparam.enable_gpio);
		if (ret) {
			dev_warn(&pdev->dev,
				 "USB function not selected (GPIO %d)\n",
				 priv->dparam.enable_gpio);
			ret = -ENOTSUPP;
			goto probe_end_mod_exit;
		}
	}

	/*
	 * platform call
	 *
	 * USB phy setup might depend on CPU/Board.
	 * If platform has its callback functions,
	 * call it here.
	 */
	ret = usbhs_platform_call(priv, hardware_init, pdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "platform init failed.\n");
		goto probe_end_mod_exit;
	}

	/* reset phy for connection */
	usbhs_platform_call(priv, phy_reset, pdev);

	/* power control */
	pm_runtime_enable(&pdev->dev);
	if (!usbhsc_flags_has(priv, USBHSF_RUNTIME_PWCTRL)) {
		usbhsc_power_ctrl(priv, 1);
		usbhs_mod_autonomy_mode(priv);
	}

	/*
	 * manual call notify_hotplug for cold plug
	 */
	usbhsc_drvcllbck_notify_hotplug(pdev);

	dev_info(&pdev->dev, "probed\n");

	return ret;

probe_end_mod_exit:
	usbhs_mod_remove(priv);
probe_end_fifo_exit:
	usbhs_fifo_remove(priv);
probe_end_pipe_exit:
	usbhs_pipe_remove(priv);

	dev_info(&pdev->dev, "probe failed (%d)\n", ret);

	return ret;
}