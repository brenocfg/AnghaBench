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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int* two2word ; 

__attribute__((used)) static inline void expand16_2col2mask(u8 fg, u8 bg, u32 fgm[], u32 bgm[])
{
	bgm[0] = two2word[bg & 3];
	fgm[0] = two2word[fg & 3] ^ bgm[0];
#if BPL > 2
	bgm[1] = two2word[(bg >> 2) & 3];
	fgm[1] = two2word[(fg >> 2) & 3] ^ bgm[1];
#endif
#if BPL > 4
	bgm[2] = two2word[(bg >> 4) & 3];
	fgm[2] = two2word[(fg >> 4) & 3] ^ bgm[2];
	bgm[3] = two2word[bg >> 6];
	fgm[3] = two2word[fg >> 6] ^ bgm[3];
#endif
}