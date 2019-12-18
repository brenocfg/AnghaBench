#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rate; unsigned int byteIOIndex; int /*<<< orphan*/  state; scalar_t__ squeezing; } ;
typedef  TYPE_1__ SpongeInstance ;

/* Variables and functions */
 int /*<<< orphan*/  SnP_AddBytes (int /*<<< orphan*/ ,unsigned char const*,unsigned int,unsigned int) ; 
 size_t SnP_FastLoop_Absorb (int /*<<< orphan*/ ,unsigned int,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  SnP_Permute (int /*<<< orphan*/ ) ; 
 int SnP_width ; 
 int /*<<< orphan*/  displayBytes (int,char*,unsigned char const*,unsigned int) ; 

int SpongeAbsorb(SpongeInstance *instance, const unsigned char *data, size_t dataByteLen)
{
    size_t i, j;
    unsigned int partialBlock;
    const unsigned char *curData;
    unsigned int rateInBytes = instance->rate/8;

    if (instance->squeezing)
        return 1; /* Too late for additional input */

    i = 0;
    curData = data;
    while(i < dataByteLen) {
        if ((instance->byteIOIndex == 0) && (dataByteLen >= (i + rateInBytes))) {
#ifdef SnP_FastLoop_Absorb
            /* processing full blocks first */
            if ((rateInBytes % (SnP_width/200)) == 0) {
                /* fast lane: whole lane rate */
                j = SnP_FastLoop_Absorb(instance->state, rateInBytes/(SnP_width/200), curData, dataByteLen - i);
                i += j;
                curData += j;
            }
            else {
#endif
                for(j=dataByteLen-i; j>=rateInBytes; j-=rateInBytes) {
                    #ifdef KeccakReference
                    displayBytes(1, "Block to be absorbed", curData, rateInBytes);
                    #endif
                    SnP_AddBytes(instance->state, curData, 0, rateInBytes);
                    SnP_Permute(instance->state);
                    curData+=rateInBytes;
                }
                i = dataByteLen - j;
#ifdef SnP_FastLoop_Absorb
            }
#endif
        }
        else {
            /* normal lane: using the message queue */
            partialBlock = (unsigned int)(dataByteLen - i);
            if (partialBlock+instance->byteIOIndex > rateInBytes)
                partialBlock = rateInBytes-instance->byteIOIndex;
            #ifdef KeccakReference
            displayBytes(1, "Block to be absorbed (part)", curData, partialBlock);
            #endif
            i += partialBlock;

            SnP_AddBytes(instance->state, curData, instance->byteIOIndex, partialBlock);
            curData += partialBlock;
            instance->byteIOIndex += partialBlock;
            if (instance->byteIOIndex == rateInBytes) {
                SnP_Permute(instance->state);
                instance->byteIOIndex = 0;
            }
        }
    }
    return 0;
}