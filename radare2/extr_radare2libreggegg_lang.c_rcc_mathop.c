#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* remit; } ;
struct TYPE_8__ {char* (* regs ) (TYPE_2__*,int) ;} ;
typedef  TYPE_1__ REggEmit ;
typedef  TYPE_2__ REgg ;

/* Variables and functions */
 int get_op (char**) ; 
 scalar_t__ is_op (char) ; 
 scalar_t__ is_space (char) ; 
 int /*<<< orphan*/  is_var (char*) ; 
 int /*<<< orphan*/  rcc_internal_mathop (TYPE_2__*,char*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char* stub1 (TYPE_2__*,int) ; 
 char* stub2 (TYPE_2__*,int) ; 
 char* stub3 (TYPE_2__*,int) ; 

__attribute__((used)) static void rcc_mathop(REgg *egg, char **pos, int level) {
	REggEmit *e = egg->remit;
	int op_ret = level;
	char op, *next_pos;

	while (**pos && is_space (**pos)) {
		(*pos)++;
	}
	next_pos = *pos + 1;

	do {
		op = (is_op (**pos) && !(is_var (*pos)))? **pos: '=';
		*pos = (is_op (**pos) && !(is_var (*pos)))? *pos + 1: *pos;
		op_ret = get_op (&next_pos);
		if (op_ret > level) {
			rcc_mathop (egg, pos, op_ret);
			rcc_internal_mathop (egg, e->regs (egg, op_ret - 1),
				strdup (e->regs (egg, level - 1)), op);
			next_pos = *pos + 1;
		} else {
			rcc_internal_mathop (egg, *pos, strdup (e->regs (egg, level - 1)), op);
			*pos = next_pos;
			next_pos++;
		}
	} while (**pos && op_ret >= level);

/* following code block sould not handle '-' and '/' well
    if (op_ret < level) {
        rcc_internal_mathop(egg, p, strdup(e->regs(egg, level-1)) ,'=');
        return;
    }
    op = *pos, *pos = '\x00', (*pos)++;
    rcc_mathop(egg, pos, op_ret);
    if (op_ret > level) {
        rcc_internal_mathop(egg, p, strdup(e->regs(egg, op_ret-1)), op);
        rcc_internal_mathop(egg, (char *)e->regs(egg, op_ret-1)
                            , strdup(e->regs(egg, level-1)), '=');
    }
    else rcc_internal_mathop(egg, p, strdup(e->regs(egg, level-1)), op);
*/
}