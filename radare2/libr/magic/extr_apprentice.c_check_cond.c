#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut32 ;
struct TYPE_6__ {TYPE_2__* li; } ;
struct TYPE_8__ {int flags; TYPE_1__ c; } ;
struct TYPE_7__ {int last_cond; } ;
typedef  TYPE_3__ RMagic ;

/* Variables and functions */
#define  COND_ELIF 131 
#define  COND_ELSE 130 
#define  COND_IF 129 
#define  COND_NONE 128 
 int R_MAGIC_CHECK ; 
 int /*<<< orphan*/  file_magwarn (TYPE_3__*,char*) ; 

__attribute__((used)) static int check_cond(RMagic *ms, int cond, ut32 cont_level) {
	int last_cond;
	last_cond = ms->c.li[cont_level].last_cond;

	switch (cond) {
	case COND_IF:
		if (last_cond != COND_NONE && last_cond != COND_ELIF) {
			if (ms->flags & R_MAGIC_CHECK) {
				file_magwarn (ms, "syntax error: `if'");
			}
			return -1;
		}
		last_cond = COND_IF;
		break;
	case COND_ELIF:
		if (last_cond != COND_IF && last_cond != COND_ELIF) {
			if (ms->flags & R_MAGIC_CHECK) {
				file_magwarn (ms, "syntax error: `elif'");
			}
			return -1;
		}
		last_cond = COND_ELIF;
		break;
	case COND_ELSE:
		if (last_cond != COND_IF && last_cond != COND_ELIF) {
			if (ms->flags & R_MAGIC_CHECK) {
				file_magwarn (ms, "syntax error: `else'");
			}
			return -1;
		}
		last_cond = COND_NONE;
		break;
	case COND_NONE:
		last_cond = COND_NONE;
		break;
	}

	ms->c.li[cont_level].last_cond = last_cond;
	return 0;
}