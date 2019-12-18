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
typedef  enum gs_sample_filter { ____Placeholder_gs_sample_filter } gs_sample_filter ;

/* Variables and functions */
 int GS_FILTER_ANISOTROPIC ; 
 int GS_FILTER_LINEAR ; 
 int GS_FILTER_MIN_LINEAR_MAG_MIP_POINT ; 
 int GS_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR ; 
 int GS_FILTER_MIN_MAG_LINEAR_MIP_POINT ; 
 int GS_FILTER_MIN_MAG_POINT_MIP_LINEAR ; 
 int GS_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT ; 
 int GS_FILTER_MIN_POINT_MAG_MIP_LINEAR ; 
 int GS_FILTER_POINT ; 
 scalar_t__ astrcmpi (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

enum gs_sample_filter get_sample_filter(const char *filter)
{
	if (astrcmpi(filter, "Anisotropy") == 0)
		return GS_FILTER_ANISOTROPIC;

	else if (astrcmpi(filter, "Point") == 0 ||
		 strcmp(filter, "MIN_MAG_MIP_POINT") == 0)
		return GS_FILTER_POINT;

	else if (astrcmpi(filter, "Linear") == 0 ||
		 strcmp(filter, "MIN_MAG_MIP_LINEAR") == 0)
		return GS_FILTER_LINEAR;

	else if (strcmp(filter, "MIN_MAG_POINT_MIP_LINEAR") == 0)
		return GS_FILTER_MIN_MAG_POINT_MIP_LINEAR;

	else if (strcmp(filter, "MIN_POINT_MAG_LINEAR_MIP_POINT") == 0)
		return GS_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;

	else if (strcmp(filter, "MIN_POINT_MAG_MIP_LINEAR") == 0)
		return GS_FILTER_MIN_POINT_MAG_MIP_LINEAR;

	else if (strcmp(filter, "MIN_LINEAR_MAG_MIP_POINT") == 0)
		return GS_FILTER_MIN_LINEAR_MAG_MIP_POINT;

	else if (strcmp(filter, "MIN_LINEAR_MAG_POINT_MIP_LINEAR") == 0)
		return GS_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;

	else if (strcmp(filter, "MIN_MAG_LINEAR_MIP_POINT") == 0)
		return GS_FILTER_MIN_MAG_LINEAR_MIP_POINT;

	return GS_FILTER_LINEAR;
}