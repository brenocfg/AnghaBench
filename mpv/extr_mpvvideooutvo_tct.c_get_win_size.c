#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vo {struct priv* priv; } ;
struct priv {TYPE_1__* opts; } ;
struct TYPE_2__ {int width; int height; } ;

/* Variables and functions */
 int DEFAULT_HEIGHT ; 
 int DEFAULT_WIDTH ; 

__attribute__((used)) static void get_win_size(struct vo *vo, int *out_width, int *out_height) {
    struct priv *p = vo->priv;
    *out_width = DEFAULT_WIDTH;
    *out_height = DEFAULT_HEIGHT;
#if HAVE_POSIX
    struct winsize winsize;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize) >= 0) {
        *out_width = winsize.ws_col;
        *out_height = winsize.ws_row;
    }
#endif

    if (p->opts->width > 0)
        *out_width = p->opts->width;
    if (p->opts->height > 0)
        *out_height = p->opts->height;
}