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
typedef  scalar_t__ PFNGLGETPERFQUERYINFOINTELPROC ;
typedef  scalar_t__ PFNGLGETPERFQUERYIDBYNAMEINTELPROC ;
typedef  scalar_t__ PFNGLGETPERFQUERYDATAINTELPROC ;
typedef  scalar_t__ PFNGLGETPERFCOUNTERINFOINTELPROC ;
typedef  scalar_t__ PFNGLGETNEXTPERFQUERYIDINTELPROC ;
typedef  scalar_t__ PFNGLGETFIRSTPERFQUERYIDINTELPROC ;
typedef  scalar_t__ PFNGLENDPERFQUERYINTELPROC ;
typedef  scalar_t__ PFNGLDELETEPERFQUERYINTELPROC ;
typedef  scalar_t__ PFNGLCREATEPERFQUERYINTELPROC ;
typedef  scalar_t__ PFNGLBEGINPERFQUERYINTELPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_INTEL_performance_query ; 
 scalar_t__ glad_glBeginPerfQueryINTEL ; 
 scalar_t__ glad_glCreatePerfQueryINTEL ; 
 scalar_t__ glad_glDeletePerfQueryINTEL ; 
 scalar_t__ glad_glEndPerfQueryINTEL ; 
 scalar_t__ glad_glGetFirstPerfQueryIdINTEL ; 
 scalar_t__ glad_glGetNextPerfQueryIdINTEL ; 
 scalar_t__ glad_glGetPerfCounterInfoINTEL ; 
 scalar_t__ glad_glGetPerfQueryDataINTEL ; 
 scalar_t__ glad_glGetPerfQueryIdByNameINTEL ; 
 scalar_t__ glad_glGetPerfQueryInfoINTEL ; 

__attribute__((used)) static void load_GL_INTEL_performance_query(GLADloadproc load) {
	if(!GLAD_GL_INTEL_performance_query) return;
	glad_glBeginPerfQueryINTEL = (PFNGLBEGINPERFQUERYINTELPROC)load("glBeginPerfQueryINTEL");
	glad_glCreatePerfQueryINTEL = (PFNGLCREATEPERFQUERYINTELPROC)load("glCreatePerfQueryINTEL");
	glad_glDeletePerfQueryINTEL = (PFNGLDELETEPERFQUERYINTELPROC)load("glDeletePerfQueryINTEL");
	glad_glEndPerfQueryINTEL = (PFNGLENDPERFQUERYINTELPROC)load("glEndPerfQueryINTEL");
	glad_glGetFirstPerfQueryIdINTEL = (PFNGLGETFIRSTPERFQUERYIDINTELPROC)load("glGetFirstPerfQueryIdINTEL");
	glad_glGetNextPerfQueryIdINTEL = (PFNGLGETNEXTPERFQUERYIDINTELPROC)load("glGetNextPerfQueryIdINTEL");
	glad_glGetPerfCounterInfoINTEL = (PFNGLGETPERFCOUNTERINFOINTELPROC)load("glGetPerfCounterInfoINTEL");
	glad_glGetPerfQueryDataINTEL = (PFNGLGETPERFQUERYDATAINTELPROC)load("glGetPerfQueryDataINTEL");
	glad_glGetPerfQueryIdByNameINTEL = (PFNGLGETPERFQUERYIDBYNAMEINTELPROC)load("glGetPerfQueryIdByNameINTEL");
	glad_glGetPerfQueryInfoINTEL = (PFNGLGETPERFQUERYINFOINTELPROC)load("glGetPerfQueryInfoINTEL");
}