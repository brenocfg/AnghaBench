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
typedef  int /*<<< orphan*/  CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  kVTProfileLevel_H264_Baseline_AutoLevel ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_High_AutoLevel ; 
 int /*<<< orphan*/  kVTProfileLevel_H264_Main_AutoLevel ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static CFStringRef obs_to_vt_profile(const char *profile)
{
	if (strcmp(profile, "baseline") == 0)
		return kVTProfileLevel_H264_Baseline_AutoLevel;
	else if (strcmp(profile, "main") == 0)
		return kVTProfileLevel_H264_Main_AutoLevel;
	else if (strcmp(profile, "high") == 0)
		return kVTProfileLevel_H264_High_AutoLevel;
	else
		return kVTProfileLevel_H264_Main_AutoLevel;
}