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
typedef  int /*<<< orphan*/  TS_RESP_CTX ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  ENV_CLOCK_PRECISION_DIGITS ; 
 int /*<<< orphan*/  NCONF_get_number_e (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,long*) ; 
 long TS_MAX_CLOCK_PRECISION_DIGITS ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_clock_precision_digits (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  ts_CONF_invalid (char const*,int /*<<< orphan*/ ) ; 

int TS_CONF_set_clock_precision_digits(CONF *conf, const char *section,
                                       TS_RESP_CTX *ctx)
{
    int ret = 0;
    long digits = 0;

    /*
     * If not specified, set the default value to 0, i.e. sec precision
     */
    if (!NCONF_get_number_e(conf, section, ENV_CLOCK_PRECISION_DIGITS,
                            &digits))
        digits = 0;
    if (digits < 0 || digits > TS_MAX_CLOCK_PRECISION_DIGITS) {
        ts_CONF_invalid(section, ENV_CLOCK_PRECISION_DIGITS);
        goto err;
    }

    if (!TS_RESP_CTX_set_clock_precision_digits(ctx, digits))
        goto err;

    return 1;
 err:
    return ret;
}