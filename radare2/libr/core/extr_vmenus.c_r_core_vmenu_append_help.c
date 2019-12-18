#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* context; } ;
struct TYPE_4__ {char* args; char* help; char* reset; } ;
struct TYPE_5__ {TYPE_1__ pal; scalar_t__ color_mode; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_2__ RConsContext ;

/* Variables and functions */
 TYPE_3__* r_cons_singleton () ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,char const*,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static void r_core_vmenu_append_help (RStrBuf *p, const char **help) {
	int i;
	RConsContext *cons_ctx = r_cons_singleton ()->context;
	const char *pal_args_color = cons_ctx->color_mode ? cons_ctx->pal.args : "",
		   *pal_help_color = cons_ctx->color_mode ? cons_ctx->pal.help : "",
		   *pal_reset = cons_ctx->color_mode ? cons_ctx->pal.reset : "";

	for (i = 0; help[i]; i += 2) {
		r_strbuf_appendf (p, "%s%s %s%s%s",
			 pal_args_color, help[i],
			 pal_help_color, help[i + 1], pal_reset);
	}
}