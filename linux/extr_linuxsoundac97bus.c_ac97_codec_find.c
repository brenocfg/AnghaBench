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
struct ac97_controller {struct ac97_codec_device** codecs; } ;
struct ac97_codec_device {int dummy; } ;

/* Variables and functions */
 unsigned int AC97_BUS_MAX_CODECS ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ac97_codec_device* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ac97_codec_device *
ac97_codec_find(struct ac97_controller *ac97_ctrl, unsigned int codec_num)
{
	if (codec_num >= AC97_BUS_MAX_CODECS)
		return ERR_PTR(-EINVAL);

	return ac97_ctrl->codecs[codec_num];
}