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
typedef  void* u8 ;
struct halmac_ver {void* minor_ver; void* prototype_ver; void* major_ver; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 scalar_t__ HALMAC_MAJOR_VER ; 
 scalar_t__ HALMAC_MINOR_VER ; 
 scalar_t__ HALMAC_PROTOTYPE_VER ; 
 int HALMAC_RET_SUCCESS ; 

enum halmac_ret_status halmac_get_version(struct halmac_ver *version)
{
	version->major_ver = (u8)HALMAC_MAJOR_VER;
	version->prototype_ver = (u8)HALMAC_PROTOTYPE_VER;
	version->minor_ver = (u8)HALMAC_MINOR_VER;

	return HALMAC_RET_SUCCESS;
}