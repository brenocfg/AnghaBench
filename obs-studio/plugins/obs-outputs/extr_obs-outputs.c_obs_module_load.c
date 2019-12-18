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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flv_output_info ; 
 int /*<<< orphan*/  ftl_output_info ; 
 int /*<<< orphan*/  null_output_info ; 
 int /*<<< orphan*/  obs_register_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtmp_output_info ; 

bool obs_module_load(void)
{
#ifdef _WIN32
	WSADATA wsad;
	WSAStartup(MAKEWORD(2, 2), &wsad);
#endif

	obs_register_output(&rtmp_output_info);
	obs_register_output(&null_output_info);
	obs_register_output(&flv_output_info);
#if COMPILE_FTL
	obs_register_output(&ftl_output_info);
#endif
	return true;
}