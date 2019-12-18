#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rate; unsigned int byteIOIndex; int /*<<< orphan*/  state; int /*<<< orphan*/  squeezing; } ;
typedef  TYPE_1__ SpongeInstance ;

/* Variables and functions */
 int /*<<< orphan*/  SnP_ExtractBytes (int /*<<< orphan*/ ,unsigned char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  SnP_Permute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpongeAbsorbLastFewBits (TYPE_1__*,int) ; 
 int /*<<< orphan*/  displayBytes (int,char*,unsigned char*,unsigned int) ; 

int SpongeSqueeze(SpongeInstance *instance, unsigned char *data, size_t dataByteLen)
{
    size_t i, j;
    unsigned int partialBlock;
    unsigned int rateInBytes = instance->rate/8;
    unsigned char *curData;

    if (!instance->squeezing)
        SpongeAbsorbLastFewBits(instance, 0x01);

    i = 0;
    curData = data;
    while(i < dataByteLen) {
        if ((instance->byteIOIndex == rateInBytes) && (dataByteLen >= (i + rateInBytes))) {
            for(j=dataByteLen-i; j>=rateInBytes; j-=rateInBytes) {
                SnP_Permute(instance->state);
                SnP_ExtractBytes(instance->state, curData, 0, rateInBytes);
                #ifdef KeccakReference
                displayBytes(1, "Squeezed block", curData, rateInBytes);
                #endif
                curData+=rateInBytes;
            }
            i = dataByteLen - j;
        }
        else {
            /* normal lane: using the message queue */
            if (instance->byteIOIndex == rateInBytes) {
                SnP_Permute(instance->state);
                instance->byteIOIndex = 0;
            }
            partialBlock = (unsigned int)(dataByteLen - i);
            if (partialBlock+instance->byteIOIndex > rateInBytes)
                partialBlock = rateInBytes-instance->byteIOIndex;
            i += partialBlock;

            SnP_ExtractBytes(instance->state, curData, instance->byteIOIndex, partialBlock);
            #ifdef KeccakReference
            displayBytes(1, "Squeezed block (part)", curData, partialBlock);
            #endif
            curData += partialBlock;
            instance->byteIOIndex += partialBlock;
        }
    }
    return 0;
}