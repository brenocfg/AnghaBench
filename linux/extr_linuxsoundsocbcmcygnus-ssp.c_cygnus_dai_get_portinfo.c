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
struct snd_soc_dai {size_t id; } ;
struct cygnus_audio {struct cygnus_aio_port* portinfo; } ;
struct cygnus_aio_port {int dummy; } ;

/* Variables and functions */
 struct cygnus_audio* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static struct cygnus_aio_port *cygnus_dai_get_portinfo(struct snd_soc_dai *dai)
{
	struct cygnus_audio *cygaud = snd_soc_dai_get_drvdata(dai);

	return &cygaud->portinfo[dai->id];
}