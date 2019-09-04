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
typedef  enum ath6kl_hif_type { ____Placeholder_ath6kl_hif_type } ath6kl_hif_type ;

/* Variables and functions */
#define  ATH6KL_HIF_TYPE_SDIO 129 
#define  ATH6KL_HIF_TYPE_USB 128 

__attribute__((used)) static const char *ath6kl_init_get_hif_name(enum ath6kl_hif_type type)
{
	switch (type) {
	case ATH6KL_HIF_TYPE_SDIO:
		return "sdio";
	case ATH6KL_HIF_TYPE_USB:
		return "usb";
	}

	return NULL;
}