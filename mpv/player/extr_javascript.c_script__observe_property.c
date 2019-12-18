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
typedef  int /*<<< orphan*/  mpv_format ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  const MPV_FORMAT_DOUBLE ; 
 int /*<<< orphan*/  const MPV_FORMAT_FLAG ; 
 int /*<<< orphan*/  const MPV_FORMAT_NODE ; 
 int /*<<< orphan*/  const MPV_FORMAT_NONE ; 
 int /*<<< orphan*/  const MPV_FORMAT_STRING ; 
 size_t checkopt (int /*<<< orphan*/ *,int,char*,char const**,char*) ; 
 int /*<<< orphan*/  jclient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsL_checkuint64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 int mpv_observe_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_status (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void script__observe_property(js_State *J)
{
    const char *fmts[] = {"none", "native", "bool", "string", "number", NULL};
    const mpv_format mf[] = {MPV_FORMAT_NONE, MPV_FORMAT_NODE, MPV_FORMAT_FLAG,
                             MPV_FORMAT_STRING, MPV_FORMAT_DOUBLE};

    mpv_format f = mf[checkopt(J, 3, "none", fmts, "observe type")];
    int e = mpv_observe_property(jclient(J), jsL_checkuint64(J, 1),
                                             js_tostring(J, 2),
                                             f);
    push_status(J, e);
}