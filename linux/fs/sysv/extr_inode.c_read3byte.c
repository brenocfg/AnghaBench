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
struct sysv_sb_info {scalar_t__ s_bytesex; } ;

/* Variables and functions */
 scalar_t__ BYTESEX_LE ; 
 scalar_t__ BYTESEX_PDP ; 

__attribute__((used)) static inline void read3byte(struct sysv_sb_info *sbi,
	unsigned char * from, unsigned char * to)
{
	if (sbi->s_bytesex == BYTESEX_PDP) {
		to[0] = from[0];
		to[1] = 0;
		to[2] = from[1];
		to[3] = from[2];
	} else if (sbi->s_bytesex == BYTESEX_LE) {
		to[0] = from[0];
		to[1] = from[1];
		to[2] = from[2];
		to[3] = 0;
	} else {
		to[0] = 0;
		to[1] = from[0];
		to[2] = from[1];
		to[3] = from[2];
	}
}