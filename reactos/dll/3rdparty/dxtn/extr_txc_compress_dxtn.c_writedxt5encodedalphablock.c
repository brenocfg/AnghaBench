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
typedef  int GLubyte ;

/* Variables and functions */

__attribute__((used)) static void writedxt5encodedalphablock( GLubyte *blkaddr, GLubyte alphabase1, GLubyte alphabase2,
                         GLubyte alphaenc[16])
{
   *blkaddr++ = alphabase1;
   *blkaddr++ = alphabase2;
   *blkaddr++ = alphaenc[0] | (alphaenc[1] << 3) | ((alphaenc[2] & 3) << 6);
   *blkaddr++ = (alphaenc[2] >> 2) | (alphaenc[3] << 1) | (alphaenc[4] << 4) | ((alphaenc[5] & 1) << 7);
   *blkaddr++ = (alphaenc[5] >> 1) | (alphaenc[6] << 2) | (alphaenc[7] << 5);
   *blkaddr++ = alphaenc[8] | (alphaenc[9] << 3) | ((alphaenc[10] & 3) << 6);
   *blkaddr++ = (alphaenc[10] >> 2) | (alphaenc[11] << 1) | (alphaenc[12] << 4) | ((alphaenc[13] & 1) << 7);
   *blkaddr++ = (alphaenc[13] >> 1) | (alphaenc[14] << 2) | (alphaenc[15] << 5);
}