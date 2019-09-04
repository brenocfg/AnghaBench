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
typedef  enum led_status_t { ____Placeholder_led_status_t } led_status_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int EPERM ; 
#define  TPACPI_LED_570 130 
 int const TPACPI_LED_BLINK ; 
 int /*<<< orphan*/  TPACPI_LED_EC_HLBL ; 
 int /*<<< orphan*/  TPACPI_LED_EC_HLCL ; 
 int /*<<< orphan*/  TPACPI_LED_EC_HLMS ; 
#define  TPACPI_LED_NEW 129 
 unsigned int const TPACPI_LED_NUMLEDS ; 
 int const TPACPI_LED_OFF ; 
#define  TPACPI_LED_OLD 128 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,unsigned int const,unsigned int const) ; 
 int ec_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  led_handle ; 
 int led_supported ; 
 int tpacpi_is_led_restricted (unsigned int const) ; 
 int* tpacpi_led_state_cache ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int led_set_status(const unsigned int led,
			  const enum led_status_t ledstatus)
{
	/* off, on, blink. Index is led_status_t */
	static const unsigned int led_sled_arg1[] = { 0, 1, 3 };
	static const unsigned int led_led_arg1[] = { 0, 0x80, 0xc0 };

	int rc = 0;

	switch (led_supported) {
	case TPACPI_LED_570:
		/* 570 */
		if (unlikely(led > 7))
			return -EINVAL;
		if (unlikely(tpacpi_is_led_restricted(led)))
			return -EPERM;
		if (!acpi_evalf(led_handle, NULL, NULL, "vdd",
				(1 << led), led_sled_arg1[ledstatus]))
			rc = -EIO;
		break;
	case TPACPI_LED_OLD:
		/* 600e/x, 770e, 770x, A21e, A2xm/p, T20-22, X20 */
		if (unlikely(led > 7))
			return -EINVAL;
		if (unlikely(tpacpi_is_led_restricted(led)))
			return -EPERM;
		rc = ec_write(TPACPI_LED_EC_HLMS, (1 << led));
		if (rc >= 0)
			rc = ec_write(TPACPI_LED_EC_HLBL,
				      (ledstatus == TPACPI_LED_BLINK) << led);
		if (rc >= 0)
			rc = ec_write(TPACPI_LED_EC_HLCL,
				      (ledstatus != TPACPI_LED_OFF) << led);
		break;
	case TPACPI_LED_NEW:
		/* all others */
		if (unlikely(led >= TPACPI_LED_NUMLEDS))
			return -EINVAL;
		if (unlikely(tpacpi_is_led_restricted(led)))
			return -EPERM;
		if (!acpi_evalf(led_handle, NULL, NULL, "vdd",
				led, led_led_arg1[ledstatus]))
			rc = -EIO;
		break;
	default:
		rc = -ENXIO;
	}

	if (!rc)
		tpacpi_led_state_cache[led] = ledstatus;

	return rc;
}