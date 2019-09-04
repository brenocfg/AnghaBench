#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mChannelsPerFrame; scalar_t__ mFormatID; scalar_t__ mBitsPerChannel; scalar_t__ mSampleRate; } ;
typedef  TYPE_1__ AudioStreamBasicDescription ;

/* Variables and functions */
 scalar_t__ MP_NUM_CHANNELS ; 
 int /*<<< orphan*/  value_is_better (scalar_t__,scalar_t__,scalar_t__) ; 

bool ca_asbd_is_better(AudioStreamBasicDescription *req,
                       AudioStreamBasicDescription *old,
                       AudioStreamBasicDescription *new)
{
    if (new->mChannelsPerFrame > MP_NUM_CHANNELS)
        return false;
    if (old->mChannelsPerFrame > MP_NUM_CHANNELS)
        return true;
    if (req->mFormatID != new->mFormatID)
        return false;
    if (req->mFormatID != old->mFormatID)
        return true;

    if (!value_is_better(req->mBitsPerChannel, old->mBitsPerChannel,
                         new->mBitsPerChannel))
        return false;

    if (!value_is_better(req->mSampleRate, old->mSampleRate, new->mSampleRate))
        return false;

    if (!value_is_better(req->mChannelsPerFrame, old->mChannelsPerFrame,
                         new->mChannelsPerFrame))
        return false;

    return true;
}