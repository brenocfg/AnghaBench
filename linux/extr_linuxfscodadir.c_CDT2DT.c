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

/* Variables and functions */
#define  CDT_BLK 136 
#define  CDT_CHR 135 
#define  CDT_DIR 134 
#define  CDT_FIFO 133 
#define  CDT_LNK 132 
#define  CDT_REG 131 
#define  CDT_SOCK 130 
#define  CDT_UNKNOWN 129 
#define  CDT_WHT 128 
 unsigned int DT_BLK ; 
 unsigned int DT_CHR ; 
 unsigned int DT_DIR ; 
 unsigned int DT_FIFO ; 
 unsigned int DT_LNK ; 
 unsigned int DT_REG ; 
 unsigned int DT_SOCK ; 
 unsigned int DT_UNKNOWN ; 
 unsigned int DT_WHT ; 

__attribute__((used)) static inline unsigned int CDT2DT(unsigned char cdt)
{
	unsigned int dt;

	switch(cdt) {
	case CDT_UNKNOWN: dt = DT_UNKNOWN; break;
	case CDT_FIFO:	  dt = DT_FIFO;    break;
	case CDT_CHR:	  dt = DT_CHR;     break;
	case CDT_DIR:	  dt = DT_DIR;     break;
	case CDT_BLK:	  dt = DT_BLK;     break;
	case CDT_REG:	  dt = DT_REG;     break;
	case CDT_LNK:	  dt = DT_LNK;     break;
	case CDT_SOCK:	  dt = DT_SOCK;    break;
	case CDT_WHT:	  dt = DT_WHT;     break;
	default:	  dt = DT_UNKNOWN; break;
	}
	return dt;
}