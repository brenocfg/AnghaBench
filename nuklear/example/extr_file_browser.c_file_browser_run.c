#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nk_rect {int /*<<< orphan*/  h; } ;
struct nk_image {int dummy; } ;
struct TYPE_5__ {float x; } ;
struct TYPE_6__ {TYPE_1__ spacing; } ;
struct TYPE_7__ {TYPE_2__ window; } ;
struct nk_context {TYPE_3__ style; } ;
struct TYPE_8__ {struct nk_image directory; struct nk_image computer; struct nk_image desktop; struct nk_image home; } ;
struct media {TYPE_4__ icons; } ;
struct file_browser {char* directory; char* home; char* desktop; size_t dir_count; size_t file_count; char** files; char* file; char** directories; struct media* media; } ;

/* Variables and functions */
 size_t MAX_PATH_LEN ; 
 int /*<<< orphan*/  NK_DYNAMIC ; 
 int /*<<< orphan*/  NK_TEXT_CENTERED ; 
#define  NK_UNDEFINED 128 
 int NK_WINDOW_BORDER ; 
 int NK_WINDOW_MOVABLE ; 
 int NK_WINDOW_NO_SCROLLBAR ; 
 int /*<<< orphan*/  file_browser_reload_directory_content (struct file_browser*,char*) ; 
 struct nk_image* media_icon_for_file (struct media*,char*) ; 
 scalar_t__ nk_begin (struct nk_context*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nk_button_image (struct nk_context*,struct nk_image) ; 
 scalar_t__ nk_button_image_label (struct nk_context*,struct nk_image,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nk_button_label (struct nk_context*,char*) ; 
 int /*<<< orphan*/  nk_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_group_begin (struct nk_context*,char*,int) ; 
 int /*<<< orphan*/  nk_group_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_label (struct nk_context*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_layout_row (struct nk_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (struct nk_context*,int,int) ; 
 int /*<<< orphan*/  nk_menubar_begin (struct nk_context*) ; 
 int /*<<< orphan*/  nk_menubar_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 struct nk_rect nk_window_get_content_region (struct nk_context*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static int
file_browser_run(struct file_browser *browser, struct nk_context *ctx)
{
    int ret = 0;
    struct media *media = browser->media;
    struct nk_rect total_space;

    if (nk_begin(ctx, "File Browser", nk_rect(50, 50, 800, 600),
        NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_MOVABLE))
    {
        static float ratio[] = {0.25f, NK_UNDEFINED};
        float spacing_x = ctx->style.window.spacing.x;

        /* output path directory selector in the menubar */
        ctx->style.window.spacing.x = 0;
        nk_menubar_begin(ctx);
        {
            char *d = browser->directory;
            char *begin = d + 1;
            nk_layout_row_dynamic(ctx, 25, 6);
            while (*d++) {
                if (*d == '/') {
                    *d = '\0';
                    if (nk_button_label(ctx, begin)) {
                        *d++ = '/'; *d = '\0';
                        file_browser_reload_directory_content(browser, browser->directory);
                        break;
                    }
                    *d = '/';
                    begin = d + 1;
                }
            }
        }
        nk_menubar_end(ctx);
        ctx->style.window.spacing.x = spacing_x;

        /* window layout */
        total_space = nk_window_get_content_region(ctx);
        nk_layout_row(ctx, NK_DYNAMIC, total_space.h, 2, ratio);
        nk_group_begin(ctx, "Special", NK_WINDOW_NO_SCROLLBAR);
        {
            struct nk_image home = media->icons.home;
            struct nk_image desktop = media->icons.desktop;
            struct nk_image computer = media->icons.computer;

            nk_layout_row_dynamic(ctx, 40, 1);
            if (nk_button_image_label(ctx, home, "home", NK_TEXT_CENTERED))
                file_browser_reload_directory_content(browser, browser->home);
            if (nk_button_image_label(ctx,desktop,"desktop",NK_TEXT_CENTERED))
                file_browser_reload_directory_content(browser, browser->desktop);
            if (nk_button_image_label(ctx,computer,"computer",NK_TEXT_CENTERED))
                file_browser_reload_directory_content(browser, "/");
            nk_group_end(ctx);
        }

        /* output directory content window */
        nk_group_begin(ctx, "Content", 0);
        {
            int index = -1;
            size_t i = 0, j = 0, k = 0;
            size_t rows = 0, cols = 0;
            size_t count = browser->dir_count + browser->file_count;

            cols = 4;
            rows = count / cols;
            for (i = 0; i <= rows; i += 1) {
                {size_t n = j + cols;
                nk_layout_row_dynamic(ctx, 135, (int)cols);
                for (; j < count && j < n; ++j) {
                    /* draw one row of icons */
                    if (j < browser->dir_count) {
                        /* draw and execute directory buttons */
                        if (nk_button_image(ctx,media->icons.directory))
                            index = (int)j;
                    } else {
                        /* draw and execute files buttons */
                        struct nk_image *icon;
                        size_t fileIndex = ((size_t)j - browser->dir_count);
                        icon = media_icon_for_file(media,browser->files[fileIndex]);
                        if (nk_button_image(ctx, *icon)) {
                            strncpy(browser->file, browser->directory, MAX_PATH_LEN);
                            n = strlen(browser->file);
                            strncpy(browser->file + n, browser->files[fileIndex], MAX_PATH_LEN - n);
                            ret = 1;
                        }
                    }
                }}
                {size_t n = k + cols;
                nk_layout_row_dynamic(ctx, 20, (int)cols);
                for (; k < count && k < n; k++) {
                    /* draw one row of labels */
                    if (k < browser->dir_count) {
                        nk_label(ctx, browser->directories[k], NK_TEXT_CENTERED);
                    } else {
                        size_t t = k-browser->dir_count;
                        nk_label(ctx,browser->files[t],NK_TEXT_CENTERED);
                    }
                }}
            }

            if (index != -1) {
                size_t n = strlen(browser->directory);
                strncpy(browser->directory + n, browser->directories[index], MAX_PATH_LEN - n);
                n = strlen(browser->directory);
                if (n < MAX_PATH_LEN - 1) {
                    browser->directory[n] = '/';
                    browser->directory[n+1] = '\0';
                }
                file_browser_reload_directory_content(browser, browser->directory);
            }
            nk_group_end(ctx);
        }
    }
    nk_end(ctx);
    return ret;
}