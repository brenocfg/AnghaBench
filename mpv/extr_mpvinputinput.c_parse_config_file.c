#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct input_ctx {int /*<<< orphan*/  global; } ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_4__ {scalar_t__ start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct input_ctx*,char*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct input_ctx*,char*,char*,...) ; 
 int /*<<< orphan*/  free_stream (int /*<<< orphan*/ *) ; 
 char* mp_get_user_path (void*,int /*<<< orphan*/ ,char*) ; 
 int parse_config (struct input_ctx*,int,TYPE_1__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stream_open (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ stream_read_complete (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  stream_skip_bom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_config_file(struct input_ctx *ictx, char *file, bool warn)
{
    int r = 0;
    void *tmp = talloc_new(NULL);
    stream_t *s = NULL;

    file = mp_get_user_path(tmp, ictx->global, file);

    s = stream_open(file, ictx->global);
    if (!s) {
        MP_ERR(ictx, "Can't open input config file %s.\n", file);
        goto done;
    }
    stream_skip_bom(s);
    bstr data = stream_read_complete(s, tmp, 1000000);
    if (data.start) {
        MP_VERBOSE(ictx, "Parsing input config file %s\n", file);
        int num = parse_config(ictx, false, data, file, NULL);
        MP_VERBOSE(ictx, "Input config file %s parsed: %d binds\n", file, num);
        r = 1;
    } else {
        MP_ERR(ictx, "Error reading input config file %s\n", file);
    }

done:
    free_stream(s);
    talloc_free(tmp);
    return r;
}