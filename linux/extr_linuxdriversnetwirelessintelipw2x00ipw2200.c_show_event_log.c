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
typedef  int u32 ;
struct ipw_priv {int dummy; } ;
struct ipw_event {int time; int event; int /*<<< orphan*/  data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int PAGE_SIZE ; 
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ipw_capture_event_log (struct ipw_priv*,int,struct ipw_event*) ; 
 int ipw_get_event_log_len (struct ipw_priv*) ; 
 int /*<<< orphan*/  kfree (struct ipw_event*) ; 
 struct ipw_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,...) ; 

__attribute__((used)) static ssize_t show_event_log(struct device *d,
			      struct device_attribute *attr, char *buf)
{
	struct ipw_priv *priv = dev_get_drvdata(d);
	u32 log_len = ipw_get_event_log_len(priv);
	u32 log_size;
	struct ipw_event *log;
	u32 len = 0, i;

	/* not using min() because of its strict type checking */
	log_size = PAGE_SIZE / sizeof(*log) > log_len ?
			sizeof(*log) * log_len : PAGE_SIZE;
	log = kzalloc(log_size, GFP_KERNEL);
	if (!log) {
		IPW_ERROR("Unable to allocate memory for log\n");
		return 0;
	}
	log_len = log_size / sizeof(*log);
	ipw_capture_event_log(priv, log_len, log);

	len += snprintf(buf + len, PAGE_SIZE - len, "%08X", log_len);
	for (i = 0; i < log_len; i++)
		len += snprintf(buf + len, PAGE_SIZE - len,
				"\n%08X%08X%08X",
				log[i].time, log[i].event, log[i].data);
	len += snprintf(buf + len, PAGE_SIZE - len, "\n");
	kfree(log);
	return len;
}