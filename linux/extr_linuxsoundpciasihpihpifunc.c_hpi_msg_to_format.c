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
struct hpi_format {scalar_t__ unused; scalar_t__ mode_legacy; int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  attributes; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  sample_rate; } ;

/* Variables and functions */

__attribute__((used)) static void hpi_msg_to_format(struct hpi_format *pF,
	struct hpi_msg_format *pMF)
{
	pF->sample_rate = pMF->sample_rate;
	pF->bit_rate = pMF->bit_rate;
	pF->attributes = pMF->attributes;
	pF->channels = pMF->channels;
	pF->format = pMF->format;
	pF->mode_legacy = 0;
	pF->unused = 0;
}