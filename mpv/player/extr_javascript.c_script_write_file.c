#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_5__ {TYPE_1__* mpctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  global; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  add_af_file (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*,char const*) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 char* mp_get_user_path (void*,int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 
 char const* strstr (char const*,char const*) ; 

__attribute__((used)) static void script_write_file(js_State *J, void *af)
{
    static const char *prefix = "file://";
    const char *fname = js_tostring(J, 1);
    const char *data = js_tostring(J, 2);
    if (strstr(fname, prefix) != fname)  // simple protection for incorrect use
        js_error(J, "File name must be prefixed with '%s'", prefix);
    fname += strlen(prefix);
    fname = mp_get_user_path(af, jctx(J)->mpctx->global, fname);
    MP_VERBOSE(jctx(J), "Writing file '%s'\n", fname);

    FILE *f = fopen(fname, "wb");
    if (!f)
        js_error(J, "Cannot open file for writing: '%s'", fname);
    add_af_file(af, f);

    int len = strlen(data);  // limited by terminating null
    int wrote = fwrite(data, 1, len, f);
    if (len != wrote)
        js_error(J, "Cannot write to file: '%s'", fname);
}