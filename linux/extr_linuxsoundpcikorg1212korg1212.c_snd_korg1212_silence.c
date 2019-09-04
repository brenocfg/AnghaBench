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
struct snd_korg1212 {TYPE_1__* playDataBufsPtr; } ;
struct KorgAudioFrame {int dummy; } ;
struct TYPE_2__ {struct KorgAudioFrame* bufferData; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  K1212_DEBUG_PRINTK_VERBOSE (char*,int,int,int,int) ; 
 int K1212_MAX_SAMPLES ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int snd_korg1212_silence(struct snd_korg1212 *korg1212, int pos, int count, int offset, int size)
{
	struct KorgAudioFrame * dst =  korg1212->playDataBufsPtr[0].bufferData + pos;
	int i;

	K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_silence pos=%d offset=%d size=%d count=%d\n",
				   pos, offset, size, count);
	if (snd_BUG_ON(pos + count > K1212_MAX_SAMPLES))
		return -EINVAL;

	for (i=0; i < count; i++) {
#if K1212_DEBUG_LEVEL > 0
		if ( (void *) dst < (void *) korg1212->playDataBufsPtr ||
		     (void *) dst > (void *) korg1212->playDataBufsPtr[8].bufferData ) {
			printk(KERN_DEBUG "K1212_DEBUG: snd_korg1212_silence KERNEL EFAULT dst=%p iter=%d\n",
			       dst, i);
			return -EFAULT;
		}
#endif
		memset((void*) dst + offset, 0, size);
		dst++;
	}

	return 0;
}