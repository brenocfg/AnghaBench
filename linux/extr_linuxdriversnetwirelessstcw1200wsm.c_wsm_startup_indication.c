#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wsm_buf {int dummy; } ;
struct TYPE_4__ {int status; int fw_cap; int fw_type; void* fw_api; void* fw_build; void* fw_ver; scalar_t__* fw_label; void* hw_subid; void* hw_id; void* input_buffer_size; void* input_buffers; } ;
struct cw1200_common {int firmware_ready; int /*<<< orphan*/  wsm_startup_done; TYPE_3__* hw; TYPE_1__ wsm_caps; } ;
struct TYPE_6__ {TYPE_2__* wiphy; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** bands; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WSM_GET (struct wsm_buf*,scalar_t__*,int) ; 
 void* WSM_GET16 (struct wsm_buf*) ; 
 int /*<<< orphan*/ * cw1200_fw_types ; 
 int /*<<< orphan*/  pr_info (char*,void*,void*,void*,void*,int /*<<< orphan*/ ,scalar_t__*,void*,void*,void*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wsm_startup_indication(struct cw1200_common *priv,
					struct wsm_buf *buf)
{
	priv->wsm_caps.input_buffers     = WSM_GET16(buf);
	priv->wsm_caps.input_buffer_size = WSM_GET16(buf);
	priv->wsm_caps.hw_id	  = WSM_GET16(buf);
	priv->wsm_caps.hw_subid	  = WSM_GET16(buf);
	priv->wsm_caps.status	  = WSM_GET16(buf);
	priv->wsm_caps.fw_cap	  = WSM_GET16(buf);
	priv->wsm_caps.fw_type	  = WSM_GET16(buf);
	priv->wsm_caps.fw_api	  = WSM_GET16(buf);
	priv->wsm_caps.fw_build   = WSM_GET16(buf);
	priv->wsm_caps.fw_ver     = WSM_GET16(buf);
	WSM_GET(buf, priv->wsm_caps.fw_label, sizeof(priv->wsm_caps.fw_label));
	priv->wsm_caps.fw_label[sizeof(priv->wsm_caps.fw_label) - 1] = 0; /* Do not trust FW too much... */

	if (WARN_ON(priv->wsm_caps.status))
		return -EINVAL;

	if (WARN_ON(priv->wsm_caps.fw_type > 4))
		return -EINVAL;

	pr_info("CW1200 WSM init done.\n"
		"   Input buffers: %d x %d bytes\n"
		"   Hardware: %d.%d\n"
		"   %s firmware [%s], ver: %d, build: %d,"
		"   api: %d, cap: 0x%.4X\n",
		priv->wsm_caps.input_buffers,
		priv->wsm_caps.input_buffer_size,
		priv->wsm_caps.hw_id, priv->wsm_caps.hw_subid,
		cw1200_fw_types[priv->wsm_caps.fw_type],
		priv->wsm_caps.fw_label, priv->wsm_caps.fw_ver,
		priv->wsm_caps.fw_build,
		priv->wsm_caps.fw_api, priv->wsm_caps.fw_cap);

	/* Disable unsupported frequency bands */
	if (!(priv->wsm_caps.fw_cap & 0x1))
		priv->hw->wiphy->bands[NL80211_BAND_2GHZ] = NULL;
	if (!(priv->wsm_caps.fw_cap & 0x2))
		priv->hw->wiphy->bands[NL80211_BAND_5GHZ] = NULL;

	priv->firmware_ready = 1;
	wake_up(&priv->wsm_startup_done);
	return 0;

underflow:
	WARN_ON(1);
	return -EINVAL;
}