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
typedef  int /*<<< orphan*/  UINT64 ;

/* Variables and functions */

void KeccakP1600_AddLanes(void *state, const unsigned char *data, unsigned int laneCount)
{
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    unsigned int i = 0;
#ifdef NO_MISALIGNED_ACCESSES
    /* If either pointer is misaligned, fall back to byte-wise xor. */
    if (((((uintptr_t)state) & 7) != 0) || ((((uintptr_t)data) & 7) != 0)) {
      for (i = 0; i < laneCount * 8; i++) {
        ((unsigned char*)state)[i] ^= data[i];
      }
    }
    else
#endif
    {
      /* Otherwise... */
      for( ; (i+8)<=laneCount; i+=8) {
          ((UINT64*)state)[i+0] ^= ((UINT64*)data)[i+0];
          ((UINT64*)state)[i+1] ^= ((UINT64*)data)[i+1];
          ((UINT64*)state)[i+2] ^= ((UINT64*)data)[i+2];
          ((UINT64*)state)[i+3] ^= ((UINT64*)data)[i+3];
          ((UINT64*)state)[i+4] ^= ((UINT64*)data)[i+4];
          ((UINT64*)state)[i+5] ^= ((UINT64*)data)[i+5];
          ((UINT64*)state)[i+6] ^= ((UINT64*)data)[i+6];
          ((UINT64*)state)[i+7] ^= ((UINT64*)data)[i+7];
      }
      for( ; (i+4)<=laneCount; i+=4) {
          ((UINT64*)state)[i+0] ^= ((UINT64*)data)[i+0];
          ((UINT64*)state)[i+1] ^= ((UINT64*)data)[i+1];
          ((UINT64*)state)[i+2] ^= ((UINT64*)data)[i+2];
          ((UINT64*)state)[i+3] ^= ((UINT64*)data)[i+3];
      }
      for( ; (i+2)<=laneCount; i+=2) {
          ((UINT64*)state)[i+0] ^= ((UINT64*)data)[i+0];
          ((UINT64*)state)[i+1] ^= ((UINT64*)data)[i+1];
      }
      if (i<laneCount) {
          ((UINT64*)state)[i+0] ^= ((UINT64*)data)[i+0];
      }
    }
#else
    unsigned int i;
    UINT8 *curData = data;
    for(i=0; i<laneCount; i++, curData+=8) {
        UINT64 lane = (UINT64)curData[0]
            | ((UINT64)curData[1] << 8)
            | ((UINT64)curData[2] << 16)
            | ((UINT64)curData[3] << 24)
            | ((UINT64)curData[4] <<32)
            | ((UINT64)curData[5] << 40)
            | ((UINT64)curData[6] << 48)
            | ((UINT64)curData[7] << 56);
        ((UINT64*)state)[i] ^= lane;
    }
#endif
}