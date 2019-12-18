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
struct snd_card_asihpi {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_asihpi_proc_read ; 
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct snd_card_asihpi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_asihpi_proc_init(struct snd_card_asihpi *asihpi)
{
	snd_card_ro_proc_new(asihpi->card, "info", asihpi,
			     snd_asihpi_proc_read);
}