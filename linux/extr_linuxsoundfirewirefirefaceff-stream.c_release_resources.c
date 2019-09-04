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
struct snd_ff {int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  tx_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_iso_resources_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_resources(struct snd_ff *ff)
{
	fw_iso_resources_free(&ff->tx_resources);
	fw_iso_resources_free(&ff->rx_resources);
}