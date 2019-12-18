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
typedef  scalar_t__ PFNGLSELECTPERFMONITORCOUNTERSAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORGROUPSTRINGAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORGROUPSAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORCOUNTERSAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORCOUNTERINFOAMDPROC ;
typedef  scalar_t__ PFNGLGETPERFMONITORCOUNTERDATAAMDPROC ;
typedef  scalar_t__ PFNGLGENPERFMONITORSAMDPROC ;
typedef  scalar_t__ PFNGLENDPERFMONITORAMDPROC ;
typedef  scalar_t__ PFNGLDELETEPERFMONITORSAMDPROC ;
typedef  scalar_t__ PFNGLBEGINPERFMONITORAMDPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_AMD_performance_monitor ; 
 scalar_t__ glad_glBeginPerfMonitorAMD ; 
 scalar_t__ glad_glDeletePerfMonitorsAMD ; 
 scalar_t__ glad_glEndPerfMonitorAMD ; 
 scalar_t__ glad_glGenPerfMonitorsAMD ; 
 scalar_t__ glad_glGetPerfMonitorCounterDataAMD ; 
 scalar_t__ glad_glGetPerfMonitorCounterInfoAMD ; 
 scalar_t__ glad_glGetPerfMonitorCounterStringAMD ; 
 scalar_t__ glad_glGetPerfMonitorCountersAMD ; 
 scalar_t__ glad_glGetPerfMonitorGroupStringAMD ; 
 scalar_t__ glad_glGetPerfMonitorGroupsAMD ; 
 scalar_t__ glad_glSelectPerfMonitorCountersAMD ; 

__attribute__((used)) static void load_GL_AMD_performance_monitor(GLADloadproc load) {
	if(!GLAD_GL_AMD_performance_monitor) return;
	glad_glGetPerfMonitorGroupsAMD = (PFNGLGETPERFMONITORGROUPSAMDPROC)load("glGetPerfMonitorGroupsAMD");
	glad_glGetPerfMonitorCountersAMD = (PFNGLGETPERFMONITORCOUNTERSAMDPROC)load("glGetPerfMonitorCountersAMD");
	glad_glGetPerfMonitorGroupStringAMD = (PFNGLGETPERFMONITORGROUPSTRINGAMDPROC)load("glGetPerfMonitorGroupStringAMD");
	glad_glGetPerfMonitorCounterStringAMD = (PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC)load("glGetPerfMonitorCounterStringAMD");
	glad_glGetPerfMonitorCounterInfoAMD = (PFNGLGETPERFMONITORCOUNTERINFOAMDPROC)load("glGetPerfMonitorCounterInfoAMD");
	glad_glGenPerfMonitorsAMD = (PFNGLGENPERFMONITORSAMDPROC)load("glGenPerfMonitorsAMD");
	glad_glDeletePerfMonitorsAMD = (PFNGLDELETEPERFMONITORSAMDPROC)load("glDeletePerfMonitorsAMD");
	glad_glSelectPerfMonitorCountersAMD = (PFNGLSELECTPERFMONITORCOUNTERSAMDPROC)load("glSelectPerfMonitorCountersAMD");
	glad_glBeginPerfMonitorAMD = (PFNGLBEGINPERFMONITORAMDPROC)load("glBeginPerfMonitorAMD");
	glad_glEndPerfMonitorAMD = (PFNGLENDPERFMONITORAMDPROC)load("glEndPerfMonitorAMD");
	glad_glGetPerfMonitorCounterDataAMD = (PFNGLGETPERFMONITORCOUNTERDATAAMDPROC)load("glGetPerfMonitorCounterDataAMD");
}