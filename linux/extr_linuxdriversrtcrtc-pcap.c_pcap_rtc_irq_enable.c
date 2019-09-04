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
struct pcap_rtc {int /*<<< orphan*/  pcap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pcap_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_to_irq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcap_rtc_irq_enable(struct device *dev, int pirq, unsigned int en)
{
	struct pcap_rtc *pcap_rtc = dev_get_drvdata(dev);

	if (en)
		enable_irq(pcap_to_irq(pcap_rtc->pcap, pirq));
	else
		disable_irq(pcap_to_irq(pcap_rtc->pcap, pirq));

	return 0;
}