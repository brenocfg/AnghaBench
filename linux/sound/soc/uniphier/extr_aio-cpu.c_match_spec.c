#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ dir; } ;
struct uniphier_aio_spec {scalar_t__ gname; scalar_t__ name; TYPE_1__ swm; } ;

/* Variables and functions */
 scalar_t__ PORT_DIR_INPUT ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static bool match_spec(const struct uniphier_aio_spec *spec,
		       const char *name, int dir)
{
	if (dir == SNDRV_PCM_STREAM_PLAYBACK &&
	    spec->swm.dir != PORT_DIR_OUTPUT) {
		return false;
	}

	if (dir == SNDRV_PCM_STREAM_CAPTURE &&
	    spec->swm.dir != PORT_DIR_INPUT) {
		return false;
	}

	if (spec->name && strcmp(spec->name, name) == 0)
		return true;

	if (spec->gname && strcmp(spec->gname, name) == 0)
		return true;

	return false;
}