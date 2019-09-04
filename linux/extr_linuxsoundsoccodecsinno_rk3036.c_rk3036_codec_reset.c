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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INNO_R00 ; 
 int INNO_R00_CDCR_RESET ; 
 int INNO_R00_CDCR_WORK ; 
 int INNO_R00_CSR_RESET ; 
 int INNO_R00_CSR_WORK ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rk3036_codec_reset(struct snd_soc_component *component)
{
	snd_soc_component_write(component, INNO_R00,
		      INNO_R00_CSR_RESET | INNO_R00_CDCR_RESET);
	snd_soc_component_write(component, INNO_R00,
		      INNO_R00_CSR_WORK | INNO_R00_CDCR_WORK);
}