#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {unsigned long value; unsigned long lo; } ;
struct TYPE_14__ {unsigned long value; unsigned long hi; } ;
struct TYPE_13__ {unsigned long value; unsigned long hi; } ;
struct TYPE_12__ {unsigned long value; unsigned long lo; } ;
struct TYPE_11__ {unsigned long value; unsigned long lo; } ;
struct TYPE_10__ {unsigned long value; unsigned long hi; } ;
struct ipw2100_priv {int status; unsigned long connect_start; unsigned long config; unsigned long capability; unsigned long fatal_error; unsigned long stop_hang_check; unsigned long stop_rf_kill; unsigned long messages_sent; unsigned long reset_backoff; TYPE_8__* ieee; TYPE_7__ txq_stat; TYPE_6__ fw_pend_stat; TYPE_5__ msg_pend_stat; TYPE_4__ msg_free_stat; TYPE_3__ tx_free_stat; TYPE_2__ tx_pend_stat; scalar_t__ last_rtc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_9__ {unsigned long* crypt; size_t tx_keyidx; } ;
struct TYPE_16__ {unsigned long scans; TYPE_1__ crypt_info; } ;

/* Variables and functions */
 int STATUS_ASSOCIATED ; 
 struct ipw2100_priv* dev_get_drvdata (struct device*) ; 
 unsigned long ktime_get_boottime_seconds () ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t show_internals(struct device *d, struct device_attribute *attr,
			      char *buf)
{
	struct ipw2100_priv *priv = dev_get_drvdata(d);
	int len = 0;

#define DUMP_VAR(x,y) len += sprintf(buf + len, # x ": %" y "\n", priv-> x)

	if (priv->status & STATUS_ASSOCIATED)
		len += sprintf(buf + len, "connected: %llu\n",
			       ktime_get_boottime_seconds() - priv->connect_start);
	else
		len += sprintf(buf + len, "not connected\n");

	DUMP_VAR(ieee->crypt_info.crypt[priv->ieee->crypt_info.tx_keyidx], "p");
	DUMP_VAR(status, "08lx");
	DUMP_VAR(config, "08lx");
	DUMP_VAR(capability, "08lx");

	len +=
	    sprintf(buf + len, "last_rtc: %lu\n",
		    (unsigned long)priv->last_rtc);

	DUMP_VAR(fatal_error, "d");
	DUMP_VAR(stop_hang_check, "d");
	DUMP_VAR(stop_rf_kill, "d");
	DUMP_VAR(messages_sent, "d");

	DUMP_VAR(tx_pend_stat.value, "d");
	DUMP_VAR(tx_pend_stat.hi, "d");

	DUMP_VAR(tx_free_stat.value, "d");
	DUMP_VAR(tx_free_stat.lo, "d");

	DUMP_VAR(msg_free_stat.value, "d");
	DUMP_VAR(msg_free_stat.lo, "d");

	DUMP_VAR(msg_pend_stat.value, "d");
	DUMP_VAR(msg_pend_stat.hi, "d");

	DUMP_VAR(fw_pend_stat.value, "d");
	DUMP_VAR(fw_pend_stat.hi, "d");

	DUMP_VAR(txq_stat.value, "d");
	DUMP_VAR(txq_stat.lo, "d");

	DUMP_VAR(ieee->scans, "d");
	DUMP_VAR(reset_backoff, "lld");

	return len;
}