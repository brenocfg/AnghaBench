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
struct hpi_msg_format {int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  attributes; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  sample_rate; } ;
struct hpi_format {int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  attributes; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  sample_rate; } ;

/* Variables and functions */

void hpi_format_to_msg(struct hpi_msg_format *pMF,
	const struct hpi_format *pF)
{
	pMF->sample_rate = pF->sample_rate;
	pMF->bit_rate = pF->bit_rate;
	pMF->attributes = pF->attributes;
	pMF->channels = pF->channels;
	pMF->format = pF->format;
}