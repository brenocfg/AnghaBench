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
struct snd_aes_iec958 {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
#define  SNDRV_CTL_ELEM_TYPE_BYTES 131 
#define  SNDRV_CTL_ELEM_TYPE_ENUMERATED 130 
#define  SNDRV_CTL_ELEM_TYPE_IEC958 129 
#define  SNDRV_CTL_ELEM_TYPE_INTEGER64 128 

__attribute__((used)) static int get_elem_size(int type, int count)
{
	switch (type) {
	case SNDRV_CTL_ELEM_TYPE_INTEGER64:
		return sizeof(s64) * count;
	case SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		return sizeof(int) * count;
	case SNDRV_CTL_ELEM_TYPE_BYTES:
		return 512;
	case SNDRV_CTL_ELEM_TYPE_IEC958:
		return sizeof(struct snd_aes_iec958);
	default:
		return -1;
	}
}