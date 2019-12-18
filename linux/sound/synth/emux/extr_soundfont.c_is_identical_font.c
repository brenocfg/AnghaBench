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
struct snd_soundfont {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SFNT_PATCH_NAME_LEN ; 
 int SNDRV_SFNT_PAT_SHARED ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_identical_font(struct snd_soundfont *sf, int type, unsigned char *name)
{
	return ((sf->type & SNDRV_SFNT_PAT_SHARED) &&
		(sf->type & 0x0f) == (type & 0x0f) &&
		(name == NULL ||
		 memcmp(sf->name, name, SNDRV_SFNT_PATCH_NAME_LEN) == 0));
}