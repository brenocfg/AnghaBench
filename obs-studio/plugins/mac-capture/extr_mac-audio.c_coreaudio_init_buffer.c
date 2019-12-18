#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct coreaudio_data {TYPE_3__* buf_list; int /*<<< orphan*/  device_id; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  frames ;
typedef  size_t UInt32 ;
struct TYPE_9__ {size_t mNumberBuffers; TYPE_1__* mBuffers; } ;
struct TYPE_8__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {size_t mDataByteSize; void* mData; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  TYPE_2__ AudioObjectPropertyAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AudioObjectGetPropertyData (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,TYPE_3__*) ; 
 int /*<<< orphan*/  AudioObjectGetPropertyDataSize (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  SCOPE_GLOBAL ; 
 int /*<<< orphan*/  bfree (TYPE_3__*) ; 
 void* bmalloc (size_t) ; 
 int /*<<< orphan*/  ca_success (int /*<<< orphan*/ ,struct coreaudio_data*,char*,char*) ; 
 int /*<<< orphan*/  get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*) ; 
 int /*<<< orphan*/  kAudioDevicePropertyBufferFrameSize ; 
 int /*<<< orphan*/  kAudioDevicePropertyScopeInput ; 
 int /*<<< orphan*/  kAudioDevicePropertyStreamConfiguration ; 
 int /*<<< orphan*/  kAudioObjectPropertyElementMaster ; 

__attribute__((used)) static bool coreaudio_init_buffer(struct coreaudio_data *ca)
{
	UInt32 buf_size = 0;
	UInt32 size = 0;
	UInt32 frames = 0;
	OSStatus stat;

	AudioObjectPropertyAddress addr = {
		kAudioDevicePropertyStreamConfiguration,
		kAudioDevicePropertyScopeInput,
		kAudioObjectPropertyElementMaster};

	stat = AudioObjectGetPropertyDataSize(ca->device_id, &addr, 0, NULL,
					      &buf_size);
	if (!ca_success(stat, ca, "coreaudio_init_buffer", "get list size"))
		return false;

	size = sizeof(frames);
	stat = get_property(ca->unit, kAudioDevicePropertyBufferFrameSize,
			    SCOPE_GLOBAL, 0, &frames, &size);
	if (!ca_success(stat, ca, "coreaudio_init_buffer", "get frame size"))
		return false;

	/* ---------------------- */

	ca->buf_list = bmalloc(buf_size);

	stat = AudioObjectGetPropertyData(ca->device_id, &addr, 0, NULL,
					  &buf_size, ca->buf_list);
	if (!ca_success(stat, ca, "coreaudio_init_buffer", "allocate")) {
		bfree(ca->buf_list);
		ca->buf_list = NULL;
		return false;
	}

	for (UInt32 i = 0; i < ca->buf_list->mNumberBuffers; i++) {
		size = ca->buf_list->mBuffers[i].mDataByteSize;
		ca->buf_list->mBuffers[i].mData = bmalloc(size);
	}

	return true;
}