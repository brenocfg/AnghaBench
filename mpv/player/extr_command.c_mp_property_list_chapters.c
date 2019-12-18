#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mpv_node {int dummy; } ;
struct m_property {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  playback_initialized; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_PRINT 129 
#define  M_PROPERTY_SET 128 
 char* chapter_display_name (TYPE_1__*,int) ; 
 double chapter_start_time (TYPE_1__*,int) ; 
 int get_chapter_count (TYPE_1__*) ; 
 int /*<<< orphan*/  get_chapter_entry ; 
 int get_current_chapter (TYPE_1__*) ; 
 char* list_current ; 
 char* list_normal ; 
 int m_property_read_list (int,void*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* mp_format_time (double,int) ; 
 int parse_node_chapters (TYPE_1__*,struct mpv_node*) ; 
 char* talloc_asprintf_append (char*,char*,...) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int mp_property_list_chapters(void *ctx, struct m_property *prop,
                                     int action, void *arg)
{
    MPContext *mpctx = ctx;
    int count = get_chapter_count(mpctx);
    switch (action) {
    case M_PROPERTY_PRINT: {
        int cur = mpctx->playback_initialized ? get_current_chapter(mpctx) : -1;
        char *res = NULL;
        int n;

        if (count < 1) {
            res = talloc_asprintf_append(res, "No chapters.");
        }

        for (n = 0; n < count; n++) {
            char *name = chapter_display_name(mpctx, n);
            double t = chapter_start_time(mpctx, n);
            char* time = mp_format_time(t, false);
            res = talloc_asprintf_append(res, "%s", time);
            talloc_free(time);
            const char *m = n == cur ? list_current : list_normal;
            res = talloc_asprintf_append(res, "   %s%s\n", m, name);
            talloc_free(name);
        }

        *(char **)arg = res;
        return M_PROPERTY_OK;
    }
    case M_PROPERTY_SET: {
        struct mpv_node *given_chapters = arg;
        return parse_node_chapters(mpctx, given_chapters);
    }
    }
    return m_property_read_list(action, arg, count, get_chapter_entry, mpctx);
}