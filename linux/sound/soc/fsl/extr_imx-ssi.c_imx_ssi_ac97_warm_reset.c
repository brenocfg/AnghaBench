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
struct snd_ac97 {int dummy; } ;
struct imx_ssi {int /*<<< orphan*/  (* ac97_warm_reset ) (struct snd_ac97*) ;} ;

/* Variables and functions */
 struct imx_ssi* ac97_ssi ; 
 int /*<<< orphan*/  imx_ssi_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_ac97*) ; 

__attribute__((used)) static void imx_ssi_ac97_warm_reset(struct snd_ac97 *ac97)
{
	struct imx_ssi *imx_ssi = ac97_ssi;

	if (imx_ssi->ac97_warm_reset)
		imx_ssi->ac97_warm_reset(ac97);

	/* First read sometimes fails, do a dummy read */
	imx_ssi_ac97_read(ac97, 0);
}