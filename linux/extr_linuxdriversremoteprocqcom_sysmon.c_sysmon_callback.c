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
typedef  int /*<<< orphan*/  u32 ;
struct rpmsg_device {int dummy; } ;
struct qcom_sysmon {int ssr_ack; int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (void*,char const*,int const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int sysmon_callback(struct rpmsg_device *rpdev, void *data, int count,
			   void *priv, u32 addr)
{
	struct qcom_sysmon *sysmon = priv;
	const char *ssr_ack = "ssr:ack";
	const int ssr_ack_len = strlen(ssr_ack) + 1;

	if (!sysmon)
		return -EINVAL;

	if (count >= ssr_ack_len && !memcmp(data, ssr_ack, ssr_ack_len))
		sysmon->ssr_ack = true;

	complete(&sysmon->comp);

	return 0;
}