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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PARSE_SINGLE_INPUT ; 
 int /*<<< orphan*/  do_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_deinit () ; 
 int /*<<< orphan*/  mp_init () ; 
 int /*<<< orphan*/  mp_stack_ctrl_init () ; 
 int /*<<< orphan*/  mp_stack_set_limit (int) ; 

int main(int argc, char **argv) {
    mp_stack_ctrl_init();
    mp_stack_set_limit(10240);
    uint32_t heap[16*1024 / 4];
    gc_init(heap, (char*)heap + 16 * 1024);
    mp_init();
    do_str("print('hello world!')", MP_PARSE_SINGLE_INPUT);
    mp_deinit();
    return 0;
}