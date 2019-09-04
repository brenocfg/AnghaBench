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
typedef  char ut8 ;

/* Variables and functions */
 char mod (char,int) ; 

__attribute__((used)) static void rot_decrypt(ut8 key, const ut8 *inbuf, ut8 *outbuf, int buflen) {
	int i;
	for (i = 0; i < buflen; i++) {
		outbuf[i] = inbuf[i];
		if ((inbuf[i] < 'a' || inbuf[i] > 'z') && (inbuf[i] < 'A' || inbuf[i] > 'Z')) {
			continue;
		}
		outbuf[i] += 26;	//adding so that subtracting does not make it negative
		outbuf[i] -= key;
		outbuf[i] -= (inbuf[i] >= 'a' && inbuf[i] <= 'z') ? 'a' : 'A';
		outbuf[i] = mod (outbuf[i], 26);
		outbuf[i] += (inbuf[i] >= 'a' && inbuf[i] <= 'z') ? 'a' : 'A';
	}
}