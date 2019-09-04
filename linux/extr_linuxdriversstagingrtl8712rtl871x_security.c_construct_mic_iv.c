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
typedef  int uint ;
typedef  int u8 ;
typedef  int sint ;

/* Variables and functions */

__attribute__((used)) static void construct_mic_iv(u8 *mic_iv, sint qc_exists, sint a4_exists,
			     u8 *mpdu, uint payload_length, u8 *pn_vector)
{
	sint i;

	mic_iv[0] = 0x59;
	if (qc_exists && a4_exists)
		mic_iv[1] = mpdu[30] & 0x0f;    /* QoS_TC           */
	if (qc_exists && !a4_exists)
		mic_iv[1] = mpdu[24] & 0x0f;   /* mute bits 7-4    */
	if (!qc_exists)
		mic_iv[1] = 0x00;
	for (i = 2; i < 8; i++)
		mic_iv[i] = mpdu[i + 8];
	for (i = 8; i < 14; i++)
		mic_iv[i] = pn_vector[13 - i]; /* mic_iv[8:13] = PN[5:0] */
	mic_iv[14] = (unsigned char) (payload_length / 256);
	mic_iv[15] = (unsigned char) (payload_length % 256);
}