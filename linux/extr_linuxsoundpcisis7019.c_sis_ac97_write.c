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
typedef  unsigned short u32 ;
struct snd_ac97 {size_t num; int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
#define  SIS_AC97_CMD_CODEC2_WRITE 130 
#define  SIS_AC97_CMD_CODEC3_WRITE 129 
#define  SIS_AC97_CMD_CODEC_WRITE 128 
 int /*<<< orphan*/  sis_ac97_rw (int /*<<< orphan*/ ,size_t,unsigned short) ; 

__attribute__((used)) static void sis_ac97_write(struct snd_ac97 *ac97, unsigned short reg,
				unsigned short val)
{
	static const u32 cmd[3] = {
		SIS_AC97_CMD_CODEC_WRITE,
		SIS_AC97_CMD_CODEC2_WRITE,
		SIS_AC97_CMD_CODEC3_WRITE,
	};
	sis_ac97_rw(ac97->private_data, ac97->num,
			(val << 16) | (reg << 8) | cmd[ac97->num]);
}