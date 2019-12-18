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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int ADFS_FILETYPE_NONE ; 

__attribute__((used)) static inline u16 adfs_filetype(u32 loadaddr)
{
	return (loadaddr & 0xfff00000) == 0xfff00000 ?
	       (loadaddr >> 8) & 0xfff : ADFS_FILETYPE_NONE;
}