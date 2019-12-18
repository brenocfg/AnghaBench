#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int vi_mode; int /*<<< orphan*/  prompt; scalar_t__ prompt_mode; } ;
struct TYPE_8__ {TYPE_2__* context; } ;
struct TYPE_6__ {char* invalid; char* prompt; char* reset; } ;
struct TYPE_7__ {TYPE_1__ pal; scalar_t__ color_mode; } ;
typedef  TYPE_3__ RCons ;

/* Variables and functions */
#define  CONTROL_MODE 129 
 TYPE_5__ I ; 
#define  INSERT_MODE 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_3__* r_cons_singleton () ; 
 char* r_str_escape (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_newf (char*,char const*,char*,char const*) ; 

__attribute__((used)) static void __update_prompt_color () {
	RCons *cons = r_cons_singleton ();
	const char *BEGIN = "", *END = "";
	if (cons->context->color_mode) {
		if (I.prompt_mode) {
			switch (I.vi_mode) {
			case CONTROL_MODE:
				BEGIN = cons->context->pal.invalid;
				break;
			case INSERT_MODE:
			default:
				BEGIN = cons->context->pal.prompt;
				break;
			}
		} else {
			BEGIN = cons->context->pal.prompt;
		}
		END = cons->context->pal.reset;
	}
	char *prompt = r_str_escape (I.prompt);		// remote the color
	free (I.prompt);
	I.prompt = r_str_newf ("%s%s%s", BEGIN, prompt, END);
}